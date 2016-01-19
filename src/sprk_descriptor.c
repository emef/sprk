/*  =========================================================================
    sprk_descriptor -

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
    sprk_descriptor -
@discuss
@end
*/

#include "sprk_classes.h"

struct _sprk_descriptor_t {
  int hi;
};

//  --------------------------------------------------------------------------
//  Creates a new descriptor.

sprk_descriptor_t *
sprk_descriptor_new (void)
{
    sprk_descriptor_t *self = (sprk_descriptor_t *) zmalloc (sizeof (sprk_descriptor_t));
    assert (self);
    //  TODO: Initialize properties
    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_descriptor.

void
sprk_descriptor_destroy (sprk_descriptor_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_descriptor_t *self = *self_p;
        //  TODO: Free class properties
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_descriptor_test (bool verbose)
{
    printf (" * sprk_descriptor: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
