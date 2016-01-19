#include "../include/sprk.h"
#include "executor.h"

int main(int argc, char* argv[]) {
    zactor_t *executor = zactor_new (executor_actor, NULL);
    zstr_send (executor, "START");

    sprk_ctx_t *ctx = sprk_ctx_new();
    sprk_descriptor_t *descriptor = sprk_descriptor_new (
        "file:///tmp/blockdata", 0, 256, 32);
    sprk_block_t *block = sprk_block_new(descriptor , NULL);
    const char *block_id = sprk_ctx_assign_block(ctx, block);
    printf ("assigned block with id %s\n", block_id);

    sprk_block_destroy(&block);
    zactor_destroy (&executor);
    sprk_ctx_destroy(&ctx);
}
