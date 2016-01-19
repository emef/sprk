/*  =========================================================================
    sprk_transform -

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
    sprk_transform -
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_transform_t {
  int hi;
};

//  --------------------------------------------------------------------------
//  Creates a new transformation.

sprk_transform_t *
sprk_transform_new (void)
{
    sprk_transform_t *self = (sprk_transform_t *) zmalloc (sizeof (sprk_transform_t));
    assert (self);
    //  TODO: Initialize properties
    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_transform.

void
sprk_transform_destroy (sprk_transform_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_transform_t *self = *self_p;
        //  TODO: Free class properties
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_transform_test (bool verbose)
{
    printf (" * sprk_transform: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
