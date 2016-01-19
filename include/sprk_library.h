/*  =========================================================================
    sprk - SPRK wrapper

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
    =========================================================================
*/

#ifndef SPRK_LIBRARY_H_INCLUDED
#define SPRK_LIBRARY_H_INCLUDED

//  Set up environment for the application

//  External dependencies
#include <czmq.h>

//  SPRK version macros for compile-time API detection

#define SPRK_VERSION_MAJOR 0
#define SPRK_VERSION_MINOR 0
#define SPRK_VERSION_PATCH 0

#define SPRK_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define SPRK_VERSION \
    SPRK_MAKE_VERSION(SPRK_VERSION_MAJOR, SPRK_VERSION_MINOR, SPRK_VERSION_PATCH)

#if defined (__WINDOWS__)
#   if defined LIBSPRK_STATIC
#       define SPRK_EXPORT
#   elif defined LIBSPRK_EXPORTS
#       define SPRK_EXPORT __declspec(dllexport)
#   else
#       define SPRK_EXPORT __declspec(dllimport)
#   endif
#else
#   define SPRK_EXPORT
#endif

//  Opaque class structures to allow forward references
typedef struct _sprk_ctx_t sprk_ctx_t;
#define SPRK_CTX_T_DEFINED
typedef struct _sprk_dataset_t sprk_dataset_t;
#define SPRK_DATASET_T_DEFINED
typedef struct _sprk_block_t sprk_block_t;
#define SPRK_BLOCK_T_DEFINED
typedef struct _sprk_blockdata_t sprk_blockdata_t;
#define SPRK_BLOCKDATA_T_DEFINED
typedef struct _sprk_descriptor_t sprk_descriptor_t;
#define SPRK_DESCRIPTOR_T_DEFINED
typedef struct _sprk_transform_t sprk_transform_t;
#define SPRK_TRANSFORM_T_DEFINED
typedef struct _sprk_block_manager_t sprk_block_manager_t;
#define SPRK_BLOCK_MANAGER_T_DEFINED
typedef struct _sprk_msg_t sprk_msg_t;
#define SPRK_MSG_T_DEFINED


//  Public API classes
#include "sprk_ctx.h"
#include "sprk_dataset.h"
#include "sprk_block.h"
#include "sprk_blockdata.h"
#include "sprk_descriptor.h"
#include "sprk_transform.h"
#include "sprk_block_manager.h"
#include "sprk_msg.h"

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/