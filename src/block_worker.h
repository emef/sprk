/*  =========================================================================
    block_worker - Worker which operates on a single block at a time.

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef BLOCK_WORKER_H_INCLUDED
#define BLOCK_WORKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create new block_worker actor instance.
//  @TODO: Describe the purpose of this actor!
//
//      zactor_t *block_worker = zactor_new (block_worker, NULL);
//
//  Destroy block_worker instance.
//
//      zactor_destroy (&block_worker);
//
//  Enable verbose logging of commands and activity:
//
//      zstr_send (block_worker, "VERBOSE");
//      zsock_wait (block_worker);
//
//  Start block_worker actor.
//
//      zstr_sendx (block_worker, "START", NULL);
//      zsock_wait (block_worker);
//
//  Stop block_worker actor.
//
//      zstr_sendx (block_worker, "STOP", NULL);
//      zsock_wait (block_worker);
//
//  This is the block_worker constructor as a zactor_fn;
SPRK_EXPORT void
    block_worker_actor (zsock_t *pipe, void *args);

//  Self test of this actor
SPRK_EXPORT void
    block_worker_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
