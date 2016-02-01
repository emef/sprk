#include "sprk_classes.h"

int
main (int argc, char *argv[])
{
    char executors_uri[256];
    if (argc == 3)
        snprintf (executors_uri, 256, "tcp://%s:%s", argv[1], argv[2]);
    else
        snprintf (executors_uri, 256, "tcp://127.0.0.1:%s", argv[1]);

    zactor_t *executor = zactor_new (executor_actor, (void *) executors_uri);
    zstr_send (executor, "START");
    zsock_wait (executor);

    // Wait for interrupted
    zsock_wait (executor);
    zactor_destroy (&executor);
}
