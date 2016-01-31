/*  =========================================================================
    broker -

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

#ifndef BROKER_H_INCLUDED
#define BROKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create a new broker
SPRK_EXPORT broker_t *
    broker_new (const char *frontend_uri, const char *backend_uri);

//  Destroy the broker
SPRK_EXPORT void
    broker_destroy (broker_t **self_p);

//  Run the broker
SPRK_EXPORT void
    broker_run (broker_t *self);

//  Run the broker in a thread.
SPRK_EXPORT pthread_t
    broker_run_in_thread (broker_t **self_p);

//  Print properties of object
SPRK_EXPORT void
    broker_print (broker_t *self);

//  Self test of this class
SPRK_EXPORT void
    broker_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
