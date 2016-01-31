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

#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "sprk_internal.h"

typedef struct _block_t block_t;

//  Creates a new block
SPRK_EXPORT block_t *
    block_new (descriptor_t *descriptor, zlist_t *applied_transforms);

//  Destroy the block.
SPRK_EXPORT void
    block_destroy (block_t **self_p);

//  Queue a transformation to be applied to this block.
SPRK_EXPORT void
    block_queue_transform (block_t *self, transform_t *transform);

//
SPRK_EXPORT descriptor_t *
    block_descriptor (block_t *self);

//  Self test of this class.
SPRK_EXPORT void
    block_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
