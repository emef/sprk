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

#ifndef BLOCK_DATA_H_INCLUDED
#define BLOCK_DATA_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "sprk_internal.h"

SPRK_EXPORT block_data_t *
    block_data_new (const block_t *block, float *data, uint32_t length);

//  Destroy the block_data.
SPRK_EXPORT void
    block_data_destroy (block_data_t **self_p);

//  Queue a transformation to be applied to this block.
SPRK_EXPORT void
    block_data_queue_transform (block_data_t *self, transform_t *transform);

//
SPRK_EXPORT descriptor_t *
    block_data_descriptor (block_data_t *self);

//  Self test of this class.
SPRK_EXPORT void
    block_data_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
