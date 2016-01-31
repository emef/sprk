/*  =========================================================================
    block_data - TODO

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
    block_data - TODO
@discuss
@end
*/

#include "sprk_internal.h"

struct _block_data_t {
    const block_t *block;
    float *data;
    uint32_t length;
};


//  --------------------------------------------------------------------------
//  Create a new block_data.

block_data_t *
block_data_new (const block_t *block, float *data, uint32_t length)
{
    block_data_t *self = (block_data_t *) zmalloc (sizeof (block_data_t));
    assert (self);

    assert (block);
    self->block = block;
    self->data = data;
    self->length = length;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the block_data.

void
block_data_destroy (block_data_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        block_data_t *self = *self_p;
        //  TODO: Free class properties
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Queue a transformation to be applied to this block.

void
block_data_queue_transform (block_data_t *self, transform_t *transform)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//

descriptor_t *
block_data_descriptor (block_data_t *self)
{
    assert (self);
    return NULL;
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
block_data_test (bool verbose)
{
    printf (" * block_data: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
