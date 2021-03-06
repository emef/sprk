/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "qsprk.h"

///
//  Copy-construct to return the proper wrapped c types
QSprkBlock::QSprkBlock (sprk_block_t *self, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = self;
}


///
//  Creates a new block
QSprkBlock::QSprkBlock (QSprkDescriptor *descriptor, zlist_t *appliedTransforms, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = sprk_block_new (descriptor->self, appliedTransforms);
}

///
//  Destroy the sprk_block.
QSprkBlock::~QSprkBlock ()
{
    sprk_block_destroy (&self);
}

///
//  Queue a transformation to be applied to this block.
void QSprkBlock::queueTransform (QSprkTransform *transform)
{
    sprk_block_queue_transform (self, transform->self);
    
}

///
//  
QSprkDescriptor * QSprkBlock::descriptor ()
{
    QSprkDescriptor *rv = new QSprkDescriptor (sprk_block_descriptor (self));
    return rv;
}

///
//  Self test of this class.
void QSprkBlock::test (bool verbose)
{
    sprk_block_test (verbose);
    
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
