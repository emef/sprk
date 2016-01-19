/*  =========================================================================
    sprk_block - Describes a block of data, where it originates on disk (descriptor)
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
    sprk_block - Describes a block of data, where it originates on disk (descriptor)
and the transformations that are applied to it.
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_block_t {
  const char *block_id;
  sprk_descriptor_t *descriptor;
  zlist_t *applied_transforms;
  zlist_t *queued_transforms;
};

//  --------------------------------------------------------------------------
//  Creates a new block

sprk_block_t *
sprk_block_new (const char *block_id, sprk_descriptor_t *descriptor, zlist_t *applied_transforms)
{
    sprk_block_t *self = (sprk_block_t *) zmalloc (sizeof (sprk_block_t));
    assert (self);

    if (!applied_transforms) {
      applied_transforms = zlist_new();
    }

    self->block_id = block_id;
    self->descriptor = descriptor;
    self->applied_transforms = applied_transforms;
    self->queued_transforms = zlist_new ();

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_block.

void
sprk_block_destroy (sprk_block_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_block_t *self = *self_p;

        // destroy transforms
        sprk_transform_t *tform = (sprk_transform_t *) zlist_first (
            self->applied_transforms);

        while (tform) {
          sprk_transform_destroy(&tform);
          tform = (sprk_transform_t *) zlist_next (self->applied_transforms);
        }

        tform = (sprk_transform_t *) zlist_first (self->queued_transforms);
        while (tform) {
          sprk_transform_destroy(&tform);
          tform = (sprk_transform_t *) zlist_next (self->queued_transforms);
        }

        // destroy properties
        sprk_descriptor_destroy (&self->descriptor);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

const char *
sprk_block_get_id (sprk_block_t *self)
{
    assert (self);
    return self->block_id;
}



//  --------------------------------------------------------------------------
//  Queue a transformation to be applied to this block.

void
sprk_block_queue_transform (sprk_block_t *self, sprk_transform_t *transform)
{
    assert (self);
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_block_test (bool verbose)
{
    printf (" * sprk_block: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
