#include "sprk_classes.h"

int
main(int argc, char* argv[])
{
    char contexts_uri[256];
    if (argc == 3)
        snprintf (contexts_uri, 256, "tcp://%s:%s", argv[1], argv[2]);
    else
        snprintf (contexts_uri, 256, "tcp://127.0.0.1:%s", argv[1]);

    srand(time(NULL));

    sprk_ctx_t *ctx = sprk_ctx_new(contexts_uri);
    sprk_dataset_t *dataset = sprk_ctx_load_dense (ctx, "/tmp/gen.dat", 400);
    sleep (3);

    sprk_dataset_destroy (&dataset);
    sprk_ctx_destroy(&ctx);
}
