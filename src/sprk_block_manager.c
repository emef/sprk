/*  =========================================================================
    sprk_block_manager -

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

/*
@header
    sprk_block_manager -
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_block_manager_t {
    zhash_t *blocks;
};

//  --------------------------------------------------------------------------
//  Create a new block manager

sprk_block_manager_t *
sprk_block_manager_new (void)
{
    sprk_block_manager_t *self = (sprk_block_manager_t *) zmalloc (sizeof (sprk_block_manager_t));
    assert (self);

    self->blocks = zhash_new ();
    assert (self->blocks);

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the block manager

void
sprk_block_manager_destroy (sprk_block_manager_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_block_manager_t *self = *self_p;

        zhash_destroy (&self->blocks);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//

sprk_blockdata_t *
sprk_block_manager_read_and_store_block (
    sprk_block_manager_t *self, const char *block_id, sprk_block_t **block_ref)
{
    assert (self);

    // Steal ownership of the block.
    assert (block_ref);
    sprk_block_t *block = *block_ref;
    assert (block);
    *block_ref = NULL;

    sprk_blockdata_t *existing = sprk_block_manager_get_block (self, block_id);
    if (existing != NULL) {
        sprk_block_destroy (&block);
        return existing;
    }

    sprk_blockdata_t *blockdata = sprk_blockdata_new (
        block, NULL, 0);

    return blockdata;
}


//  --------------------------------------------------------------------------
//

sprk_blockdata_t *
sprk_block_manager_get_block (sprk_block_manager_t *self, const char *block_id)
{
    assert (self);

    return (sprk_blockdata_t *) zhash_lookup (self->blocks, block_id);
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_block_manager_test (bool verbose)
{
    printf (" * sprk_block_manager: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
