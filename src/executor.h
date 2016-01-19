/*  =========================================================================
    executor - Executor which manages a set of blocks which are owned by a
sprk_dataset. Delegates operations to its workers.

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef EXECUTOR_H_INCLUDED
#define EXECUTOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _executor_t executor_t;

//  @interface
//  Create new executor actor instance.
//  @TODO: Describe the purpose of this actor!
//
//      zactor_t *executor = zactor_new (executor, NULL);
//
//  Destroy executor instance.
//
//      zactor_destroy (&executor);
//
//  Enable verbose logging of commands and activity:
//
//      zstr_send (executor, "VERBOSE");
//      zsock_wait (executor);
//
//  Start executor actor.
//
//      zstr_sendx (executor, "START", NULL);
//      zsock_wait (executor);
//
//  Stop executor actor.
//
//      zstr_sendx (executor, "STOP", NULL);
//      zsock_wait (executor);
//
//  This is the executor constructor as a zactor_fn;
SPRK_EXPORT void
    executor_actor (zsock_t *pipe, void *args);

//  Self test of this actor
SPRK_EXPORT void
    executor_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
