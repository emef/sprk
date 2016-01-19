/*  =========================================================================
    blockworker - Worker which operates on a single block at a time.

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
    blockworker - Worker which operates on a single block at a time.
@discuss
@end
*/

#include "sprk_classes.h"

//  Structure of our actor

struct _blockworker_t {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?

    zsock_t *work_pull;  // PULL work requests
};


//  --------------------------------------------------------------------------
//  Create a new blockworker.

static blockworker_t *
blockworker_new (zsock_t *pipe, void *args)
{
    blockworker_t *self = (blockworker_t *) zmalloc (sizeof (blockworker_t));
    assert (self);

    self->pipe = pipe;
    self->terminated = false;
    self->poller = zpoller_new (self->pipe, NULL);

    puts ("created blockworker\n");
    self->work_pull = zsock_new_pull ("inproc://blockpush");

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the blockworker.

static void
blockworker_destroy (blockworker_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        blockworker_t *self = *self_p;

        zsock_destroy (&self->work_pull);

        //  Free object itself
        zpoller_destroy (&self->poller);
        free (self);
        *self_p = NULL;
    }
}


//  Start this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
blockworker_start (blockworker_t *self)
{
    assert (self);

    //  TODO: Add startup actions
    puts ("starting worker");
    zframe_t *msg = zframe_recv (self->work_pull);
    puts (zframe_strdup (msg));

    zframe_destroy (&msg);

    return 0;
}


//  Stop this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
blockworker_stop (blockworker_t *self)
{
    assert (self);

    //  TODO: Add shutdown actions

    return 0;
}


//  Here we handle incomming message from the node

static void
blockworker_recv_api (blockworker_t *self)
{
//  Get the whole message of the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    if (!request)
       return;        //  Interrupted

    char *command = zmsg_popstr (request);
    if (streq (command, "START"))
        zsock_signal (self->pipe, blockworker_start (self));
    else
    if (streq (command, "STOP"))
        zsock_signal (self->pipe, blockworker_stop (self));
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


//  --------------------------------------------------------------------------
//  This is the actor which runs in its own thread.

void
blockworker_actor (zsock_t *pipe, void *args)
{
    blockworker_t * self = blockworker_new (pipe, args);
    if (!self)
        return;          //  Interrupted

    //  Signal actor successfully initiated
    zsock_signal (self->pipe, 0);

    while (!self->terminated) {
       zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 0);
       if (which == self->pipe)
          blockworker_recv_api (self);
       //  Add other sockets when you need them.
    }

    blockworker_destroy (&self);
}


//  --------------------------------------------------------------------------
//  Self test of this actor.

void
blockworker_test (bool verbose)
{
    printf (" * blockworker: ");

    int rc = 0;
    //  @selftest
    //  Simple create/destroy test
    zactor_t *blockworker = zactor_new (blockworker_actor, NULL);

    zstr_send (blockworker, "START");
    rc = zsock_wait (blockworker);                 //  Wait until actor started
    assert (rc == 0);

    zstr_send (blockworker, "STOP");
    rc = zsock_wait (blockworker);                 //  Wait until actor stopped
    assert (rc == 0);

    zactor_destroy (&blockworker);
    //  @end

    printf ("OK\n");
}
