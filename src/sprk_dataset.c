/*  =========================================================================
    sprk_dataset - Distributed dataset with fixed set of operations and transformations.

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
    sprk_dataset - Distributed dataset with fixed set of operations and transformations.
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_dataset_t {
    sprk_ctx_t *ctx;  // parent context (does not own)
    zhash_t *blocks;  // map block-id to block_t (owns)
};

//  --------------------------------------------------------------------------
//  Creates a new sprk dataset from a set of input paths.

sprk_dataset_t *
sprk_dataset_new (sprk_ctx_t *context, zhash_t *blocks)
{
    sprk_dataset_t *self = (sprk_dataset_t *) zmalloc (sizeof (sprk_dataset_t));
    assert (self);

    self->ctx = context;
    self->blocks = blocks;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_dataset.

void
sprk_dataset_destroy (sprk_dataset_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_dataset_t *self = *self_p;

        block_t *block = (block_t *) zhash_first (self->blocks);
        while (block != NULL) {
            block_destroy (&block);
            zhash_delete (self->blocks, zhash_cursor (self->blocks));
            block = (block_t *) zhash_next (self->blocks);
        }
        zhash_destroy (&self->blocks);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Checkpoints all blocks and their transformations across executors.

void
sprk_dataset_checkpoint (sprk_dataset_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Multiplies all values by the multiplier.

void
sprk_dataset_mul (sprk_dataset_t *self, float multiplier)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Calculates the sum of all values in the dataset.

float
sprk_dataset_sum (sprk_dataset_t *self)
{
    assert (self);
    return 0;
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_dataset_test (bool verbose)
{
    printf (" * sprk_dataset: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
