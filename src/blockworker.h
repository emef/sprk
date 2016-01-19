/*  =========================================================================
    blockworker - Worker which operates on a single block at a time.

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef BLOCKWORKER_H_INCLUDED
#define BLOCKWORKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _blockworker_t blockworker_t;

//  @interface
//  Create new blockworker actor instance.
//  @TODO: Describe the purpose of this actor!
//
//      zactor_t *blockworker = zactor_new (blockworker, NULL);
//
//  Destroy blockworker instance.
//
//      zactor_destroy (&blockworker);
//
//  Enable verbose logging of commands and activity:
//
//      zstr_send (blockworker, "VERBOSE");
//      zsock_wait (blockworker);
//
//  Start blockworker actor.
//
//      zstr_sendx (blockworker, "START", NULL);
//      zsock_wait (blockworker);
//
//  Stop blockworker actor.
//
//      zstr_sendx (blockworker, "STOP", NULL);
//      zsock_wait (blockworker);
//
//  This is the blockworker constructor as a zactor_fn;
SPRK_EXPORT void
    blockworker_actor (zsock_t *pipe, void *args);

//  Self test of this actor
SPRK_EXPORT void
    blockworker_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
