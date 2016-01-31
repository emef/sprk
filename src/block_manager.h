/*  =========================================================================
    block_manager -

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef BLOCK_MANAGER_H_INCLUDED
#define BLOCK_MANAGER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "sprk_internal.h"

SPRK_EXPORT block_manager_t *
    block_manager_new (void);

//  Destroy the block manager
SPRK_EXPORT void
    block_manager_destroy (block_manager_t **self_p);

//
SPRK_EXPORT block_data_t *
    block_manager_read_and_store_block (
        block_manager_t *self, const char *block_id, block_t **block_ref);

//
SPRK_EXPORT block_data_t *
    block_manager_get_block (block_manager_t *self, const char *block_id);

//  Self test of this class.
SPRK_EXPORT void
    block_manager_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
