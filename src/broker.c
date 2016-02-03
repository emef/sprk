/*  =========================================================================
    broker -

    The MIT License (MIT)

    Copyright (c) 2016 Matt Forbes

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    =========================================================================
*/

/*
@header
    broker -
@discuss
@end
*/

#include "sprk_classes.h"

struct _broker_t {
    zsock_t *contexts;
    zsock_t *executors;
    zpoller_t *poller;
    zlist_t *executor_lb;
    zlist_t *backlog;
};

broker_t *
broker_new (const char *contexts_uri, const char *executors_uri)
{
    broker_t *self = (broker_t *) malloc (sizeof (broker_t));
    assert (self);

    printf ("[BROKER] binding to frontend %s\n", contexts_uri);
    self->contexts = zsock_new_router (contexts_uri);
    assert(self->contexts);

    printf ("[BROKER] binding to backend %s\n", executors_uri);
    self->executors = zsock_new_router (executors_uri);
    assert (self->executors);
    zsock_set_router_mandatory (self->executors, true);

    // Only poll on executors until we have executors available.
    self->poller = zpoller_new (self->executors, NULL);
    assert (self->poller);

    self->executor_lb = zlist_new ();
    assert (self->executor_lb);

    self->backlog = zlist_new ();
    assert (self->backlog);

    return self;
}

//  Destroy the broker
void
broker_destroy (broker_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        broker_t *self = *self_p;

        zsock_destroy (&self->contexts);
        zsock_destroy (&self->executors);
        zpoller_destroy (&self->poller);

        // TODO: delete contents of list.
        zlist_destroy (&self->executor_lb);
        zlist_destroy (&self->backlog);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

void
broker_on_cancel (void *args)
{
    broker_t *self = (broker_t *) args;
    broker_destroy (&self);
}

void *
broker_thread_run (void *args)
{
    int rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    assert (rc == 0);

    // Create broker, set cleanup handler.
    broker_t *self = (broker_t *) args;
    pthread_cleanup_push (broker_on_cancel, self);

    // Run broker until cancelled.
    broker_run (self);

    // Clean up broker and exit thread.
    pthread_cleanup_pop (1);
    pthread_exit (NULL);
}

pthread_t
broker_run_in_thread (broker_t **self_p)
{
    // Take ownership of the broker, give it to the thread.
    assert (self_p);
    broker_t *self = *self_p;
    *self_p = NULL;

    pthread_t broker_thread;
    pthread_create (&broker_thread, NULL, broker_thread_run, (void *) self);
    return broker_thread;
}

// Send a message to the next available executor. Will attempt
// to send to all available executors until send succeeds, or
// returns -1 if all fail.
int
broker_send_to_executor (broker_t *self, zmsg_t *msg)
{
    int rc = -1;
    while (rc != 0 && zlist_size (self->executor_lb)) {
        zframe_t *executor_addr = (zframe_t *) zlist_pop (self->executor_lb);
        zmsg_prepend (msg, &executor_addr);

        // [executor] [context] [request]
        rc = zmsg_send (&msg, self->executors);
        if (rc != 0) {
            zframe_t *addr_discard = zmsg_pop (msg);
            zframe_destroy (&addr_discard);
        }
    }

    return rc;
}

// Distribute all backlog messages while are workers available.
// Failed-to-send messages are put back in the backlog.
void
broker_check_backlog (broker_t *self)
{
    while (zlist_size (self->backlog) && zlist_size (self->executor_lb)) {
        zmsg_t *backlog_msg = zlist_pop (self->backlog);
        if (0 != broker_send_to_executor (self, backlog_msg))
            zlist_append (self->backlog, backlog_msg);
    }
}

void
broker_run (broker_t *self)
{
    // Only accepting requests when executors available.
    bool accepting_requests = false;

    while (1) {
        zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 10);
        if (which == self->contexts) {
            puts ("[BROKER] which == self->contexts");

            // [context] [request]
            zmsg_t *msg = zmsg_recv (self->contexts);
            assert (msg);

            if (0 != broker_send_to_executor (self, msg))
                zlist_append (self->backlog, msg);

            // Remove contexts from poller if no executors
            if (zlist_size (self->executor_lb) == 0) {
                zpoller_remove (self->poller, self->contexts);
                accepting_requests = false;
            }
        }
        else if (which == self->executors) {
            puts ("[BROKER] which == self->executors");
            // EITHER:
            //    [executor] ["READY"]
            //    [executor] [context] [response]
            zmsg_t *msg = zmsg_recv (self->executors);
            assert (msg);

            zframe_t *executor_addr = zmsg_pop (msg);
            assert (executor_addr);

            zframe_t *ctx_or_ready = zmsg_pop (msg);
            char *context_addr = zframe_strdup (ctx_or_ready);
            if (strcmp (context_addr, "READY") != 0) {
                // Forward the response to the correct context addr.
                // [context] [0] [response]
                zmsg_prepend (msg, &ctx_or_ready);
                zmsg_send (&msg, self->contexts);
            } else {
                // Got a READY message
                // Put the executor ID back in the available queue
                zlist_append (self->executor_lb, executor_addr);

                // We know at least one executor is now available,
                // so check and assign backlog tasks.
                broker_check_backlog (self);

                // If we now have executors but not accepting requests,
                // then start polling on the frontend socket.
                if (!accepting_requests && zlist_size (self->executor_lb)) {
                    zpoller_add (self->poller, self->contexts);
                    accepting_requests = true;
                }

                // Destroy the READY message.
                zmsg_destroy (&msg);
            }
        }
        else if (zpoller_terminated (self->poller))
            break;
    }
}

//  Print properties of object
void
broker_print (broker_t *self)
{
    puts ("[broker]");
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
broker_test (bool verbose)
{
    printf (" * broker: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
