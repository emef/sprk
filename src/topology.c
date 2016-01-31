#include <czmq.h>
#include <pthread.h>

/**
  client
    send [0] [request]

  broker
    recv [client] [0] [request]
    send [worker] [0] [client] [0] [request]

  worker
    recv [client] [0] [request]
    send [client] [0] [response]

  broker
    recv [worker] [0] [client] [0] [response]
    send [client] [0] [response]

  client
    recv [0] [response]
 */

void *
client_fn (void *args)
{
    zsock_t *dealer = zsock_new_dealer ("ipc://frontend.ipc");
    zstr_sendm (dealer, "");
    zstr_send (dealer, "this is my request");

    zstr_sendm (dealer, "");
    zstr_send (dealer, "second request");

    char *empty = zstr_recv (dealer);
    assert (empty[0] == 0);
    free (empty);

    char *response = zstr_recv (dealer);
    printf ("client got first response: %s\n", response);
    free (response);

    empty = zstr_recv (dealer);
    free (empty);
    response = zstr_recv (dealer);
    printf ("client got second response: %s\n", response);
    free (response);

    zsock_destroy (&dealer);
    pthread_exit (NULL);
}

void *
worker_fn (void *args)
{
    int rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    assert (rc == 0);

    zsock_t *worker = zsock_new_req ("ipc://backend.ipc");
    assert (worker);

    zstr_sendm (worker, "READY");
    zstr_send (worker, "");

    while (1) {
        zmsg_t *msg = zmsg_recv (worker);
        assert (msg);

        zframe_t *client = zmsg_pop (msg);
        assert (client);

        char *empty = zmsg_popstr (msg);
        assert(empty[0] == 0);
        free (empty);

        char *request = zmsg_popstr (msg);
        printf ("worker got request: %s\n", request);
        free (request);

        zmsg_pushstr (msg, "a response");
        zmsg_pushstr (msg, "");
        zmsg_prepend (msg, &client);

        zmsg_send (&msg, worker);
    }

    zsock_destroy (&worker);
    pthread_exit (NULL);
}

int
main (int argc, char* argv[])
{
    zsock_t *frontend = zsock_new_router ("ipc://frontend.ipc");
    zsock_t *backend = zsock_new_router ("ipc://backend.ipc");

    pthread_t clients[2];
    for (int i = 0; i < 2; i++) {
        pthread_create (&clients[i], NULL, client_fn, NULL);
    }

    pthread_t workers[5];
    for (int i = 0; i < 5; i++) {
        pthread_create (&workers[i], NULL, worker_fn, NULL);
    }

    zlist_t *available_workers = zlist_new ();
    zpoller_t *poller = zpoller_new (backend, NULL);

    int i = 3;
    while (1) {
        zsock_t *which = (zsock_t *) zpoller_wait (poller, 0);
        if (which == frontend) {
            // [client] [0] [request]
            zmsg_t *msg = zmsg_recv (frontend);
            zframe_t *worker_address = (zframe_t *) zlist_pop (available_workers);
            zframe_t *empty = zframe_new_empty();
            zmsg_prepend (msg, &empty);
            zmsg_prepend (msg, &worker_address);

            // [worker] [0] [client] [0] [request]
            zmsg_send (&msg, backend);

            // We took the last worker from the pool.
            if (zlist_size (available_workers) == 0)
                zpoller_remove (poller, frontend);
        }
        else if (which == backend) {
            // EITHER:
            //     [worker] [0] ["READY"]
            //     [worker] [0] [client] [0] [response]
            zmsg_t *msg = zmsg_recv (backend);
            assert (msg);

            // Put the worker ID back in the available queue
            zframe_t *worker_address = zmsg_pop (msg);
            assert (worker_address);
            zlist_append (available_workers, worker_address);

            // There are now worker (s) available.
            if (zlist_size (available_workers) == 1)
                zpoller_add (poller, frontend);

            char *empty = zmsg_popstr (msg);
            assert (empty[0] == 0);
            free (empty);

            zframe_t *client_or_ready = zmsg_first (msg);
            char *client_id = zframe_strdup (client_or_ready);
            if (strcmp (client_id, "READY") != 0) {
                //zmsg_prepend (msg, &client_or_ready);
                zmsg_send (&msg, frontend);
                if (i-- == 0)
                    break;
            } else {
                zmsg_destroy (&msg);
            }
        }
        else if (zpoller_terminated (poller))
            exit (0);
    }


    for (int i = 0; i < 2; i++)
        pthread_join (clients[i], NULL);
    for (int i = 0; i < 5; i++) {
        pthread_cancel (workers[i]);
        pthread_join (workers[i], NULL);
    }
}
