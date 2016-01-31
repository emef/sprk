#include "sprk_classes.h"

int
main (int argc, char *argv[])
{
    assert (argc == 2);
    char executors_uri[256];
    snprintf (executors_uri, 256, "tcp://127.0.0.1:%s", argv[1]);

    zactor_t *executor = zactor_new (executor_actor, (void *) executors_uri);
    zstr_send (executor, "START");
    zsock_wait (executor);

    // Wait for interrupted
    zsock_wait (executor);
    zactor_destroy (&executor);
}
