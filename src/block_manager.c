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

/*
@header
    block_manager -
@discuss
@end
*/

#include <pthread.h>
#include "sprk_internal.h"

struct _block_manager_t {
    pthread_mutex_t lock;
    zhash_t *blocks;
};

//  --------------------------------------------------------------------------
//  Create a new block manager

block_manager_t *
block_manager_new (void)
{
    block_manager_t *self = (block_manager_t *) zmalloc (sizeof (block_manager_t));
    assert (self);

    int rc = pthread_mutex_init(&self->lock, NULL);
    assert (rc == 0);

    self->blocks = zhash_new ();
    assert (self->blocks);

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the block manager

void
block_manager_destroy (block_manager_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        block_manager_t *self = *self_p;

        zhash_destroy (&self->blocks);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
// Read and store a block.
// Takes ownership of argument `block_ref`, which will be nullified on return.

block_data_t *
block_manager_read_and_store_block (
    block_manager_t *self, const char *block_id, block_t **block_ref)
{
    assert (self);

    // Steal ownership of the block.
    assert (block_ref);
    block_t *block = *block_ref;
    assert (block);
    *block_ref = NULL;

    block_data_t *existing = block_manager_get_block (self, block_id);
    if (existing != NULL) {
        block_destroy (&block);
        return existing;
    }

    descriptor_t *descriptor = block_descriptor (block);
    FILE *fp = fopen (descriptor_uri (descriptor), "r");
    assert (fp);
    fseek (fp, descriptor_offset (descriptor), SEEK_SET);
    uint32_t length = descriptor_length (descriptor);
    size_t floats = length / sizeof (float);
    float *data = (float *)malloc (length);
    int n = fread (data, sizeof (float), floats, fp);
    assert (n == length);
    fclose (fp);

    block_data_t *blockdata = block_data_new (
        block, data, length);

    pthread_mutex_lock(&self->lock);
    zhash_insert (self->blocks, block_id, blockdata);
    pthread_mutex_unlock(&self->lock);

    return blockdata;
}


//  --------------------------------------------------------------------------
//

block_data_t *
block_manager_get_block (block_manager_t *self, const char *block_id)
{
    assert (self);

    return (block_data_t *) zhash_lookup (self->blocks, block_id);
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
block_manager_test (bool verbose)
{
    printf (" * block_manager: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
