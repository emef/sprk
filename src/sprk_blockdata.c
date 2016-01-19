/*  =========================================================================
    sprk_blockdata - TODO

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
    sprk_blockdata - TODO
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_blockdata_t {
    sprk_block_t *block;
    float *data;
    uint32_t length;
};


//  --------------------------------------------------------------------------
//  Create a new sprk_blockdata.

sprk_blockdata_t *
sprk_blockdata_new (sprk_block_t *block, float *data, uint32_t length)
{
    sprk_blockdata_t *self = (sprk_blockdata_t *) zmalloc (sizeof (sprk_blockdata_t));
    assert (self);
    //  TODO: Initialize properties
    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_blockdata.

void
sprk_blockdata_destroy (sprk_blockdata_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_blockdata_t *self = *self_p;
        //  TODO: Free class properties
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Queue a transformation to be applied to this block.

void
sprk_blockdata_queue_transform (sprk_blockdata_t *self, sprk_transform_t *transform)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//

sprk_descriptor_t *
sprk_blockdata_descriptor (sprk_blockdata_t *self)
{
    assert (self);
    return NULL;
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_blockdata_test (bool verbose)
{
    printf (" * sprk_blockdata: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
