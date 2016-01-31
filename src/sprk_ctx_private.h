#ifndef SPRK_CTX_PRIVATE
#define SPRK_CTX_PRIVATE

#include "sprk_classes.h"

SPRK_EXPORT char *
    sprk_ctx_assign_block (sprk_ctx_t *self, block_t *block);

SPRK_EXPORT void
    sprk_ctx_drop_block (sprk_ctx_t *self, block_t *block);

#endif
