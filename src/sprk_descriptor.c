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

#define URI_LEN 1024

struct _sprk_descriptor_t {
    char uri[URI_LEN];
    uint64_t offset;
    uint64_t length;
    uint32_t row_size;
};

//  --------------------------------------------------------------------------
//  Creates a new descriptor.

sprk_descriptor_t *
sprk_descriptor_new (const char *uri, uint64_t offset, uint64_t length, uint32_t row_size)
{
    sprk_descriptor_t *self = (sprk_descriptor_t *) zmalloc (sizeof (sprk_descriptor_t));
    assert (self);

    strncpy(self->uri, uri, URI_LEN);
    self->offset = offset;
    self->length = length;
    self->row_size = row_size;

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

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

const char *
sprk_descriptor_uri (sprk_descriptor_t *self)
{
    assert (self);
    return self->uri;
}

uint64_t
sprk_descriptor_offset (sprk_descriptor_t *self)
{
    assert (self);
    return self->offset;
}

uint64_t
sprk_descriptor_length (sprk_descriptor_t *self)
{
    assert (self);
    return self->length;
}

uint32_t
sprk_descriptor_row_size (sprk_descriptor_t *self)
{
    assert (self);
    return self->row_size;
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_descriptor_test (bool verbose)
{
    printf (" * sprk_descriptor: ");

    //  @selftest
    sprk_descriptor_t *descriptor = sprk_descriptor_new (
        "file:///tmp/blockdata", 0, 256, 32);
    assert (streq("file:///tmp/blockdata", sprk_descriptor_uri (descriptor)));
    assert (0 == sprk_descriptor_offset (descriptor));
    assert (256 == sprk_descriptor_length (descriptor));
    assert (32 == sprk_descriptor_row_size (descriptor));
    sprk_descriptor_destroy (&descriptor);

    //  @end

    printf ("OK\n");
}
