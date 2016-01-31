#include "sprk_classes.h"

int
main(int argc, char* argv[])
{
    assert (argc == 2);
    char contexts_uri[256];
    snprintf (contexts_uri, 256, "tcp://127.0.0.1:%s", argv[1]);

    srand(time(NULL));

    sprk_ctx_t *ctx = sprk_ctx_new(contexts_uri);
    sprk_dataset_t *dataset = sprk_ctx_load_dense (ctx, "/tmp/gen.dat", 400);
    sleep (3);

    sprk_dataset_destroy (&dataset);
    sprk_ctx_destroy(&ctx);
}
