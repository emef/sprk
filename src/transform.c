/*  =========================================================================
    transform -

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
    transform -
@discuss
@end
*/

#include "sprk_classes.h"

struct transform_t {
    int a;
};

//  --------------------------------------------------------------------------
//  Self test of this class.

void
transform_test (bool verbose)
{
    printf (" * transform: ");

    //  @selftest
    //  @end

    printf ("OK\n");
}