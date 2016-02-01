#include "sprk_classes.h"

int
main (int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    char contexts_uri[256];
    char executors_uri[256];
    snprintf (contexts_uri, 256, "tcp://0.0.0.0:%s", argv[1]);
    snprintf (executors_uri, 256, "tcp://0.0.0.0:%s", argv[2]);

    broker_t *broker = broker_new (contexts_uri, executors_uri);
    broker_run (broker);

    broker_destroy (&broker);
}
