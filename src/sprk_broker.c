#include "sprk_classes.h"

int
main (int argc, char *argv[])
{
    assert (argc == 3);

    char contexts_uri[256];
    char executors_uri[256];

    snprintf (contexts_uri, 256, "tcp://127.0.0.1:%s", argv[1]);
    snprintf (executors_uri, 256, "tcp://127.0.0.1:%s", argv[2]);

    broker_t *broker = broker_new (contexts_uri, executors_uri);
    broker_run (broker);

    broker_destroy (&broker);
}
