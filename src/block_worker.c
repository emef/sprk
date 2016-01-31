/*  =========================================================================
    block_worker - Worker which operates on a single block at a time.

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

/*
@header
    block_worker - Worker which operates on a single block at a time.
@discuss
@end
*/

#include "sprk_internal.h"
#include <pthread.h>

//  Structure of our actor

struct _block_worker_t {
    zsock_t *pipe;                  //  Actor command pipe
    zpoller_t *poller;              //  Socket poller
    bool terminated;                //  Did caller ask us to quit?
    bool verbose;                   //  Verbose logging enabled?

    zsock_t *workers_pull;          // PULL work requests. (owns)
    zsock_t *workers_push;          // PUSH work completions. (owns)
    block_manager_t *block_manager; // Block manager. (does not own)
};


//  --------------------------------------------------------------------------
//  Create a new block_worker.

static block_worker_t *
block_worker_new (zsock_t *pipe, void *args)
{
    block_worker_t *self = (block_worker_t *) zmalloc (sizeof (block_worker_t));
    assert (self);

    self->block_manager = args;
    assert (self->block_manager);

    // Connect workers PULL socket.
    self->workers_pull = zsock_new (ZMQ_PULL);
    zsock_connect (self->workers_pull, "inproc://workers-outbound");
    assert (self->workers_pull);

    // Connect workers PUSH socket.
    self->workers_push = zsock_new (ZMQ_PUSH);
    zsock_connect (self->workers_push, "inproc://workers-inbound");
    assert (self->workers_push);

    self->pipe = pipe;
    self->terminated = false;
    self->poller = zpoller_new (self->pipe, self->workers_pull, NULL);

    printf ("worker-%lu created\n", (long) pthread_self());

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the block_worker.

static void
block_worker_destroy (block_worker_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        block_worker_t *self = *self_p;

        zsock_destroy (&self->workers_pull);
        zsock_destroy (&self->workers_push);

        //  Free object itself
        zpoller_destroy (&self->poller);
        free (self);
        *self_p = NULL;
    }
}


//  Start this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
block_worker_start (block_worker_t *self)
{
    assert (self);

    return 0;
}


//  Stop this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
block_worker_stop (block_worker_t *self)
{
    assert (self);
    self->terminated = true;

    return 0;
}

static void
block_worker_work (block_worker_t *self)
{
    zframe_t *ctx_addr = zframe_recv (self->pipe);

    // Incoming: [context] [sprk_msg]
    sprk_msg_t *msg = sprk_msg_new ();
    int rc = sprk_msg_recv (msg, self->pipe);
    assert (rc == 0);

    const char *block_id = sprk_msg_block_id (msg);

    if (sprk_msg_id (msg) == SPRK_MSG_ASSIGN_BLOCK)
        printf ("[WORKER] assigning %s\n", block_id);
    else
        assert (0);  // unhandled message

    sprk_msg_t *ack_msg = sprk_msg_new ();
    sprk_msg_set_id (ack_msg, SPRK_MSG_BLOCK_ASSIGNED);
    sprk_msg_set_block_id (ack_msg, block_id);
    zframe_send (&ctx_addr, self->pipe, ZFRAME_MORE);
    sprk_msg_send (ack_msg, self->pipe);

    sprk_msg_destroy (&msg);
    sprk_msg_destroy (&ack_msg);
}

//  Here we handle incomming message from the node

static void
block_worker_recv_api (block_worker_t *self)
{
    char *command = zstr_recv (self->pipe);
    if (!command)
        return;  // Interrupted

    if (streq (command, "WORK"))
        block_worker_work (self);
    else
    if (streq (command, "START"))
        zsock_signal (self->pipe, block_worker_start (self));
    else
    if (streq (command, "STOP"))
        zsock_signal (self->pipe, block_worker_stop (self));
    else
    if (streq (command, "VERBOSE")) {
        self->verbose = true;
        zsock_signal (self->pipe, 0);
    }
    else
    if (streq (command, "$TERM"))
        //  The $TERM command is send by zactor_destroy() method
        self->terminated = true;
    else {
        zsys_error ("invalid command '%s'", command);
        assert (false);
    }

    free (command);
}

void block_worker_assign_block (block_worker_t *self, sprk_msg_t *msg)
{
    const char *block_id = sprk_msg_block_id (msg);
    printf ("worker-%lu is handling assign_block (%s)\n",
            (long) pthread_self(), block_id);
    //sprk_msg_print (msg);

    descriptor_t *descriptor = descriptor_new (
        sprk_msg_descriptor_uri (msg), sprk_msg_descriptor_offset (msg),
        sprk_msg_descriptor_length (msg), sprk_msg_descriptor_row_size (msg));
    block_t *block = block_new (descriptor, zlist_new());
    block_data_t *blockdata = block_manager_read_and_store_block (
        self->block_manager, block_id, &block);

    assert (blockdata);

    // Notify executor that we finished loading the block.
    sprk_msg_t *notify_msg = sprk_msg_new ();
    sprk_msg_set_id (notify_msg, SPRK_MSG_BLOCK_ASSIGNED);
    sprk_msg_set_block_id (notify_msg, block_id);
    sprk_msg_send (notify_msg, self->workers_push);
    sprk_msg_destroy (&notify_msg);

}

void
block_worker_handle_workers_pull (block_worker_t *self)
{
    sprk_msg_t *msg = sprk_msg_new ();
    sprk_msg_recv (msg, self->workers_pull);

    if (sprk_msg_id (msg) == SPRK_MSG_ASSIGN_BLOCK)
        block_worker_assign_block (self, msg);
    else
        assert (0);  // unhandled message

    sprk_msg_destroy (&msg);
}


//  --------------------------------------------------------------------------
//  This is the actor which runs in its own thread.

void
block_worker_actor (zsock_t *pipe, void *args)
{
    block_worker_t * self = block_worker_new (pipe, args);
    if (!self)
        return;          //  Interrupted

    //  Signal actor successfully initiated
    zsock_signal (self->pipe, 0);

    while (!self->terminated) {
       zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 10);
       if (which == self->pipe)
          block_worker_recv_api (self);

       else
       if (which == self->workers_pull)
           block_worker_handle_workers_pull (self);
    }

    block_worker_destroy (&self);
}


//  --------------------------------------------------------------------------
//  Self test of this actor.

void
block_worker_test (bool verbose)
{
    printf (" * block_worker: ");

    int rc = 0;
    //  @selftest
    //  Simple create/destroy test
    zactor_t *block_worker = zactor_new (block_worker_actor, NULL);

    zstr_send (block_worker, "START");
    rc = zsock_wait (block_worker);                 //  Wait until actor started
    assert (rc == 0);

    zstr_send (block_worker, "STOP");
    rc = zsock_wait (block_worker);                 //  Wait until actor stopped
    assert (rc == 0);

    zactor_destroy (&block_worker);
    //  @end

    printf ("OK\n");
}
