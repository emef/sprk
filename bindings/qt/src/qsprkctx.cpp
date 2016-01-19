/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "qsprk.h"

///
//  Copy-construct to return the proper wrapped c types
QSprkCtx::QSprkCtx (sprk_ctx_t *self, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = self;
}


///
//  Creates a new sprk context which facilitates communication with
//  known executors.                                               
QSprkCtx::QSprkCtx (QObject *qObjParent) : QObject (qObjParent)
{
    this->self = sprk_ctx_new ();
}

///
//  Destroy the sprk_ctx.
QSprkCtx::~QSprkCtx ()
{
    sprk_ctx_destroy (&self);
}

///
//  Assign a block to the executor pool.
void QSprkCtx::assignBlock (QSprkBlock *block)
{
    sprk_ctx_assign_block (self, block->self);
    
}

///
//  Remove a block from the executor pool.
void QSprkCtx::dropBlock (QSprkBlock *block)
{
    sprk_ctx_drop_block (self, block->self);
    
}

///
//  Self test of this class.
void QSprkCtx::test (bool verbose)
{
    sprk_ctx_test (verbose);
    
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
