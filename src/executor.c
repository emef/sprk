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

//  Structure of our actor

struct _executor_t {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?

    zlist_t *workers;           // Contains all worker actors.
    zlist_t *worker_lb;         // Contains available worker actors.
    zsock_t *contexts;          // REQ for direct commands from context.
    block_manager_t *block_manager;  // Block manager.
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

    const char *broker_uri = (char *) args;
    printf ("[EXECUTOR] connecting to broker %s\n", broker_uri);
    self->contexts = zsock_new_dealer (broker_uri);
    assert (self->contexts);

    self->block_manager = block_manager_new ();
    assert (self->block_manager);

    self->workers = zlist_new ();
    assert (self->workers);

    self->worker_lb = zlist_new ();
    assert (self->worker_lb);

    int i;
    for (i = 0; i < 2; i++) {
        zactor_t *worker = zactor_new (block_worker_actor, self->block_manager);
        zstr_send (worker, "START");
        zsock_wait (worker);
        assert (worker);
        zlist_append (self->workers, worker);
        zlist_append (self->worker_lb, worker);
    }

    self->poller = zpoller_new (
        self->pipe,
        self->contexts,
        NULL);

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

        zsock_destroy (&self->contexts);
        block_manager_destroy (&self->block_manager);

        zactor_t *worker = (zactor_t *) zlist_first (self->workers);
        while (worker) {
            zstr_send (worker, "STOP");
            zsock_wait (worker);
            zactor_destroy (&worker);
            worker = (zactor_t *) zlist_next (self->workers);
        }

        zlist_destroy (&self->workers);
        zlist_destroy (&self->worker_lb);

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

    puts ("[EXECUTOR] start");
    zstr_send (self->contexts, "READY");

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
executor_handle_context_req (executor_t *self)
{
    puts ("[EXECUTOR] forwarding request to worker");

    // Grab the next available worker, adding it to the poller
    // so we know when it has completed its work.
    zactor_t *worker = (zactor_t *) zlist_pop (self->worker_lb);
    zpoller_add (self->poller, worker);

    assert (worker);
    zmsg_t *msg = zmsg_recv (self->contexts);
    zstr_sendm (worker, "WORK");
    zmsg_send (&msg, worker);

    // Executor ready for another task.
    zstr_send (self->contexts, "READY");
}

void
executor_handle_worker_req (executor_t *self, zactor_t *worker)
{
    puts ("[EXECUTOR] got message from a worker");
    zlist_append (self->worker_lb, worker);

    // Forward along to context.
    zmsg_t *msg = zmsg_recv (worker);
    zmsg_send (&msg, self->contexts);
}

//  --------------------------------------------------------------------------
//  This is the actor which runs in its own thread.

void
executor_actor (zsock_t *pipe, void *args)
{
    executor_t *self = executor_new (pipe, args);
    if (!self)
        return;          //  Interrupted

    //  Signal actor successfully initiated
    zsock_signal (self->pipe, 0);

    while (!self->terminated) {
       zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 10);
       if (which == self->pipe)
          executor_recv_api (self);
       else
       if (which == self->contexts)
           executor_handle_context_req (self);
       else
       if (which != NULL)
           executor_handle_worker_req (self, (zactor_t *) which);
       else
       if (zpoller_terminated (self->poller))
           break;

       if (zlist_size (self->worker_lb) == 0)
           zpoller_remove (self->poller, self-> contexts);
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
