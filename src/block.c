/*  =========================================================================
    block - Describes a block of data, where it originates on disk (descriptor)
and the transformations that are applied to it.

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
    block - Describes a block of data, where it originates on disk (descriptor)
and the transformations that are applied to it.
@discuss
@end
*/

#include "sprk_classes.h"

struct _block_t {
  descriptor_t *descriptor;
  zlist_t *applied_transforms;
  zlist_t *queued_transforms;
};

//  --------------------------------------------------------------------------
//  Creates a new block

block_t *
block_new (descriptor_t *descriptor, zlist_t *applied_transforms)
{
    block_t *self = (block_t *) zmalloc (sizeof (block_t));
    assert (self);

    if (!applied_transforms) {
      applied_transforms = zlist_new();
    }

    self->descriptor = descriptor;
    self->applied_transforms = applied_transforms;
    self->queued_transforms = zlist_new ();

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the block.

void
block_destroy (block_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        block_t *self = *self_p;

        // destroy transforms
        transform_t *tform = (transform_t *) zlist_first (
            self->applied_transforms);

        while (tform) {
          transform_destroy(&tform);
          tform = (transform_t *) zlist_next (self->applied_transforms);
        }

        tform = (transform_t *) zlist_first (self->queued_transforms);
        while (tform) {
          transform_destroy(&tform);
          tform = (transform_t *) zlist_next (self->queued_transforms);
        }

        // destroy properties
        descriptor_destroy (&self->descriptor);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

descriptor_t *
block_descriptor (block_t *self)
{
    assert (self);
    return self->descriptor;
}


//  --------------------------------------------------------------------------
//  Queue a transformation to be applied to this block.

void
block_queue_transform (block_t *self, transform_t *transform)
{
    assert (self);
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
block_test (bool verbose)
{
    printf (" * block: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
