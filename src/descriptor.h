/*  =========================================================================
    descriptor -

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef DESCRIPTOR_H_INCLUDED
#define DESCRIPTOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "sprk_internal.h"

//  @interface
//  Creates a new descriptor.
SPRK_EXPORT descriptor_t *
    descriptor_new (const char *uri, uint64_t offset, uint64_t length, uint32_t row_size);

//  Destroy the descriptor.
SPRK_EXPORT void
    descriptor_destroy (descriptor_t **self_p);

//
SPRK_EXPORT const char *
    descriptor_uri (descriptor_t *self);

//
SPRK_EXPORT uint64_t
    descriptor_offset (descriptor_t *self);

//
SPRK_EXPORT uint64_t
    descriptor_length (descriptor_t *self);

//
SPRK_EXPORT uint32_t
    descriptor_row_size (descriptor_t *self);

//  Self test of this class.
SPRK_EXPORT void
    descriptor_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
