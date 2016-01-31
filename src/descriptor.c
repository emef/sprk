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

/*
@header
    descriptor -
@discuss
@end
*/

#include "sprk_internal.h"

#define URI_LEN 1024

struct _descriptor_t {
    char uri[URI_LEN];
    uint64_t offset;
    uint64_t length;
    uint32_t row_size;
};

//  --------------------------------------------------------------------------
//  Creates a new descriptor.

descriptor_t *
descriptor_new (const char *uri, uint64_t offset, uint64_t length, uint32_t row_size)
{
    descriptor_t *self = (descriptor_t *) zmalloc (sizeof (descriptor_t));
    assert (self);

    strncpy(self->uri, uri, URI_LEN);
    self->offset = offset;
    self->length = length;
    self->row_size = row_size;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the descriptor.

void
descriptor_destroy (descriptor_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        descriptor_t *self = *self_p;

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

const char *
descriptor_uri (descriptor_t *self)
{
    assert (self);
    return self->uri;
}

uint64_t
descriptor_offset (descriptor_t *self)
{
    assert (self);
    return self->offset;
}

uint64_t
descriptor_length (descriptor_t *self)
{
    assert (self);
    return self->length;
}

uint32_t
descriptor_row_size (descriptor_t *self)
{
    assert (self);
    return self->row_size;
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
descriptor_test (bool verbose)
{
    printf (" * descriptor: ");

    //  @selftest
    descriptor_t *descriptor = descriptor_new (
        "file:///tmp/blockdata", 0, 256, 32);
    assert (streq("file:///tmp/blockdata", descriptor_uri (descriptor)));
    assert (0 == descriptor_offset (descriptor));
    assert (256 == descriptor_length (descriptor));
    assert (32 == descriptor_row_size (descriptor));
    descriptor_destroy (&descriptor);

    //  @end

    printf ("OK\n");
}
