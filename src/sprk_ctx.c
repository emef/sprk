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

#include "sprk_classes.h"

struct _sprk_ctx_t {
  zsock_t *block_push;  // PUSH blocks to executors
  zsock_t *work_pub; // PUB work requests to executors
  zsock_t *work_sub; // SUB work completions from executors
  zlist_t *datasets; // List of datasets created by this context.
};

//  --------------------------------------------------------------------------
//  Creates a new sprk context which facilitates communication with
//  known executors.

sprk_ctx_t *
sprk_ctx_new (void)
{
    sprk_ctx_t *self = (sprk_ctx_t *) zmalloc (sizeof (sprk_ctx_t));
    assert (self);

    self->block_push = zsock_new_push ("inproc://executors");
    self->work_pub = zsock_new_pub ("inproc://workpub");
    self->work_sub = zsock_new_sub ("inproc://worksub", "_");
    self->datasets = zlist_new ();

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

        // destroy the datasets.
        sprk_dataset_t *dataset = (sprk_dataset_t *) zlist_first (self->datasets);
        while (dataset) {
          sprk_dataset_destroy (&dataset);
          dataset = (sprk_dataset_t *) zlist_next (self->datasets);
        }

        // destroy properties.
        zsock_destroy (&self->block_push);
        zsock_destroy (&self->work_pub);
        zsock_destroy (&self->work_sub);
        zlist_destroy (&self->datasets);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

const char *
sprk_ctx_assign_block (sprk_ctx_t *self, sprk_block_t *block)
{
  assert(self);
  assert(block);

  sprk_msg_t *msg = sprk_msg_new ();
  sprk_descriptor_t *descriptor = sprk_block_descriptor (block);

  // TODO: wtf
  const char *block_id = "abc123";

  sprk_msg_set_id (msg, SPRK_MSG_ASSIGN_BLOCK);
  sprk_msg_set_block_id (msg, block_id);
  sprk_msg_set_descriptor_uri (msg, sprk_descriptor_uri (descriptor));
  sprk_msg_set_descriptor_offset (msg, sprk_descriptor_offset (descriptor));
  sprk_msg_set_descriptor_length (msg, sprk_descriptor_length (descriptor));
  sprk_msg_set_descriptor_row_size (msg, sprk_descriptor_row_size (descriptor));

  sprk_msg_send (msg, self->block_push);
  sprk_msg_destroy (&msg);

  return block_id;
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
