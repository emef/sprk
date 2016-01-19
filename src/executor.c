/*  =========================================================================
    executor - Executor which manages a set of blocks which are owned by a
sprk_dataset. Delegates operations to its workers.

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
    executor - Executor which manages a set of blocks which are owned by a
sprk_dataset. Delegates operations to its workers.
@discuss
@end
*/

#include "sprk_classes.h"
#include "sprk_block_manager.h"

//  Structure of our actor

struct _executor_t {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?

    zsock_t *block_pull;
    sprk_block_manager_t *block_manager;
};


//  --------------------------------------------------------------------------
//  Create a new executor.

static executor_t *
executor_new (zsock_t *pipe, void *args)
{
    executor_t *self = (executor_t *) zmalloc (sizeof (executor_t));
    assert (self);

    self->pipe = pipe;
    self->terminated = false;

    self->block_pull = zsock_new_pull ("inproc://executors");
    assert (self->block_pull);

    self->block_manager = sprk_block_manager_new ();
    assert (self->block_manager);

    self->poller = zpoller_new (self->pipe, self->block_pull, NULL);

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the executor.

static void
executor_destroy (executor_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        executor_t *self = *self_p;

        zsock_destroy (&self->block_pull);
        sprk_block_manager_destroy (&self->block_manager);

        //  Free object itself
        zpoller_destroy (&self->poller);
        free (self);
        *self_p = NULL;
    }
}


//  Start this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
executor_start (executor_t *self)
{
    assert (self);

    //  TODO: Add startup actions

    return 0;
}


//  Stop this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
executor_stop (executor_t *self)
{
    assert (self);

    //  TODO: Add shutdown actions

    return 0;
}


//  Here we handle incomming message from the node

static void
executor_recv_api (executor_t *self)
{
//  Get the whole message of the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    if (!request)
       return;        //  Interrupted

    char *command = zmsg_popstr (request);
    if (streq (command, "START"))
        zsock_signal (self->pipe, executor_start (self));
    else
    if (streq (command, "STOP"))
        zsock_signal (self->pipe, executor_stop (self));
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
}

void
executor_assign_block (executor_t *self, sprk_msg_t *msg)
{
    sprk_msg_print (msg);
    const char *block_id = sprk_msg_block_id (msg);
    sprk_descriptor_t *descriptor = sprk_descriptor_new (
        sprk_msg_descriptor_uri (msg), sprk_msg_descriptor_offset (msg),
        sprk_msg_descriptor_length (msg), sprk_msg_descriptor_row_size (msg));
    sprk_block_t *block = sprk_block_new (descriptor, zlist_new());
    sprk_blockdata_t *blockdata = sprk_block_manager_read_and_store_block (
        self->block_manager, block_id, &block);

    printf ("looked up blockdata in manager (%s)\n",
            (blockdata != NULL) ? "true" : "false");
}


void
executor_handle_block_pull (executor_t *self)
{
    sprk_msg_t *msg = sprk_msg_new ();
    int rc = sprk_msg_recv (msg, self->block_pull);
    assert (rc == 0);

    if (sprk_msg_id (msg) == SPRK_MSG_ASSIGN_BLOCK)
        executor_assign_block (self, msg);

    sprk_msg_destroy (&msg);
}

//  --------------------------------------------------------------------------
//  This is the actor which runs in its own thread.

void
executor_actor (zsock_t *pipe, void *args)
{
    executor_t * self = executor_new (pipe, args);
    if (!self)
        return;          //  Interrupted

    //  Signal actor successfully initiated
    zsock_signal (self->pipe, 0);

    while (!self->terminated) {
       zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 0);
       if (which == self->pipe)
          executor_recv_api (self);
       else
       if (which == self->block_pull)
           executor_handle_block_pull (self);
    }

    executor_destroy (&self);
}


//  --------------------------------------------------------------------------
//  Self test of this actor.

void
executor_test (bool verbose)
{
    printf (" * executor: ");

    int rc = 0;
    //  @selftest
    //  Simple create/destroy test
    zactor_t *executor = zactor_new (executor_actor, NULL);

    zstr_send (executor, "START");
    rc = zsock_wait (executor);                    //  Wait until actor started
    assert (rc == 0);

    zstr_send (executor, "STOP");
    rc = zsock_wait (executor);                    //  Wait until actor stopped
    assert (rc == 0);

    zactor_destroy (&executor);
    //  @end

    printf ("OK\n");
}
