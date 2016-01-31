/*  =========================================================================
    transform -

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "sprk_internal.h"

//  @interface
//  Creates a new transformation.
SPRK_EXPORT transform_t *
    transform_new (void);

//  Destroy the transform.
SPRK_EXPORT void
    transform_destroy (transform_t **self_p);

//  Self test of this class.
SPRK_EXPORT void
    transform_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
