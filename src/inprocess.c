#include "../include/sprk.h"
#include "blockworker.h"

int main(int argc, char* argv[]) {
    zactor_t *worker = zactor_new (blockworker_actor, NULL);
    zstr_send (worker, "START");

    sprk_ctx_t *ctx = sprk_ctx_new();
    sprk_block_t *block = sprk_block_new("1a33bf", NULL, NULL);
    sprk_ctx_assign_block(ctx, block);

    zactor_destroy (&worker);
    sprk_block_destroy(&block);
    sprk_ctx_destroy(&ctx);
}
