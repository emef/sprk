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
        zlist_destroy (&self->executor_lb);

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

void
broker_run (broker_t *self)
{
    while (1) {
        zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 10);
        if (which == self->contexts) {
            puts ("[BROKER] which == self->contexts");
            // Executor must be available if contexts is polled on.
            zframe_t *executor_addr = (zframe_t *) zlist_pop (self->executor_lb);

            // [context] [request]
            zmsg_t *msg = zmsg_recv (self->contexts);
            assert (msg);

            zmsg_prepend (msg, &executor_addr);

            // [executor] [context] [request]
            int rc = zmsg_send (&msg, self->executors);
            if (rc != 0) {
                zframe_t *addr_discard = zmsg_pop (msg);
                zframe_destroy (&addr_discard);
                zlist_append (self->backlog, msg);
            }

            // Remove contexts from poller if no executors
            if (zlist_size (self->executor_lb) == 0)
                zpoller_remove (self->poller, self->contexts);
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

                // Messages in backlog have precedence and should be
                // handled right away.
                if (zlist_size (self->backlog)) {
                    zmsg_t *backlog_msg = zlist_pop (self->backlog);
                    zmsg_prepend (backlog_msg, &executor_addr);
                    int rc = zmsg_send (&backlog_msg, self->executors);
                    if (rc != 0) {
                        zframe_t *addr_discard = zmsg_pop (backlog_msg);
                        zframe_destroy (&addr_discard);
                        zlist_append (self->backlog, backlog_msg);
                    }
                }
                else {
                    // Put the executor ID back in the available queue
                    zlist_append (self->executor_lb, executor_addr);
                }

                // There are now an executor available.
                if (zlist_size (self->executor_lb) == 1)
                    zpoller_add (self->poller, self->contexts);

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
