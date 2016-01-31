/*  =========================================================================
    sprk_ctx - sprk context; public API to work with distributed datasets.

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
    sprk_ctx - sprk context; public API to work with distributed datasets.
@discuss
@end
*/

#include <string.h>

#include "sprk_classes.h"
#include "sprk_internal.h"

struct _sprk_ctx_t {
    zpoller_t *poller; // temporary?

    zsock_t *executors;  // DEALER to executors
};

//  --------------------------------------------------------------------------
//  Creates a new sprk context which facilitates communication with
//  known executors.

sprk_ctx_t *
sprk_ctx_new (const char *broker_uri)
{
    sprk_ctx_t *self = (sprk_ctx_t *) zmalloc (sizeof (sprk_ctx_t));
    assert (self);

    printf ("[CONTEXT] connecting to broker at %s\n", broker_uri);
    self->executors = zsock_new_dealer (broker_uri);
    assert (self->executors);

    self->poller = zpoller_new (self->executors, NULL);
    assert (self->poller);

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the sprk_ctx.

void
sprk_ctx_destroy (sprk_ctx_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_ctx_t *self = *self_p;

        // destroy properties.
        zsock_destroy (&self->executors);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

char *
sprk_ctx_assign_block (sprk_ctx_t *self, block_t *block)
{
  assert(self);
  assert(block);

  // TODO: use UIDs
  static int i = 0;
  char *block_id = malloc(64 * sizeof (char));
  snprintf(block_id, 64, "block-%d", i++);

  sprk_msg_t *msg = sprk_msg_new ();
  descriptor_t *descriptor = block_descriptor (block);

  sprk_msg_set_id (msg, SPRK_MSG_ASSIGN_BLOCK);
  sprk_msg_set_block_id (msg, block_id);
  sprk_msg_set_descriptor_uri (msg, descriptor_uri (descriptor));
  sprk_msg_set_descriptor_offset (msg, descriptor_offset (descriptor));
  sprk_msg_set_descriptor_length (msg, descriptor_length (descriptor));
  sprk_msg_set_descriptor_row_size (msg, descriptor_row_size (descriptor));

  puts ("[CONTEXT] sending message to self->executors");
  sprk_msg_send (msg, self->executors);
  sprk_msg_destroy (&msg);

  return block_id;
}

void
sprk_ctx_drop_block (sprk_ctx_t *self, block_t *block)
{
}

// break a file (at `path`) into blocks, distribute them across the cluster,
// and add the new (block-id -> block_t) mappings to the `blocks` map.
void sprk_ctx_distribute_blocks (
    sprk_ctx_t *self, zhash_t *blocks, const char *path, uint32_t row_size)
{
    FILE *fp = fopen (path, "r");
    puts (path);
    assert (fp);
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    assert (sz % row_size == 0);
    fclose (fp);

    size_t max_blocks = sz / row_size;
    size_t num_blocks = max_blocks < 10 ? max_blocks : 10;
    uint32_t block_size = ((sz / num_blocks) / row_size) * row_size;

    printf ("FILE %s: %zu blocks of %d bytes\n", path, num_blocks, block_size);

    for (int i = 0; i < num_blocks; i++) {
        uint32_t offset = i * block_size;
        uint32_t length;
        if (i == num_blocks - 1) {
            length = sz - (i-1) * block_size;
        } else {
            length = block_size;
        }

        descriptor_t *descriptor = descriptor_new (path, offset, length, row_size);
        block_t *block = block_new (descriptor, zlist_new ());
        char *block_id = sprk_ctx_assign_block (self, block);
        zhash_insert (blocks, block_id, block);
    }
}


sprk_dataset_t *
sprk_ctx_load_dense (sprk_ctx_t *self, const char *path_list, uint32_t row_size)
{
    char *tofree, *string, *path;
    tofree = string = strdup (path_list);
    assert (string != NULL);

    zhash_t *blocks = zhash_new ();

    while ((path = strsep (&string, ",")) != NULL) {
        sprk_ctx_distribute_blocks (self, blocks, path, row_size);
    }

    free (tofree);

    size_t numblocks = zhash_size (blocks);
    for (int i = 0; i < numblocks; i++) {
        sprk_msg_t *msg = sprk_msg_new ();
        int rc = sprk_msg_recv (msg, self->executors);
        if (rc != 0)
            return NULL;
        sprk_msg_print (msg);
        sprk_msg_destroy (&msg);
    }

    return sprk_dataset_new (self, blocks);
}

//  --------------------------------------------------------------------------
//  Self test of this class.

void
sprk_ctx_test (bool verbose)
{
    printf (" * sprk_ctx: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}
