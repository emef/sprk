/*  =========================================================================
    executor - Executor which manages a set of blocks which are owned by a
sprk_dataset. Delegates operations to its workers.

    The MIT License (MIT)                                                         
                                                                                  
    Copyright (c) 2016 Matt Forbes                                                
                                                                                  
    Permission is hereby granted, free of charge, to any person obtaining a copy  
    of this software and associated documentation files (the "Software"), to deal 
    in the Software without restriction, including without limitation the rights  
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
    copies of the Software, and to permit persons to whom the Software is         
    furnished to do so, subject to the following conditions:                      
                                                                                  
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.                               
                                                                                  
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
    SOFTWARE.                                                                     
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
