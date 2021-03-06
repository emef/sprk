/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "qsprk.h"

///
//  Copy-construct to return the proper wrapped c types
QSprkDescriptor::QSprkDescriptor (sprk_descriptor_t *self, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = self;
}


///
//  Creates a new descriptor.
//  Creates a new descriptor.
QSprkDescriptor::QSprkDescriptor (const QString &uri, quint64 offset, quint64 length, quint32 rowSize, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = sprk_descriptor_new (uri.toUtf8().data(), (uint64_t) offset, (uint64_t) length, (uint32_t) rowSize);
}

///
//  Destroy the sprk_descriptor.
QSprkDescriptor::~QSprkDescriptor ()
{
    sprk_descriptor_destroy (&self);
}

///
//  
const QString QSprkDescriptor::uri ()
{
    const QString rv = QString (sprk_descriptor_uri (self));
    return rv;
}

///
//  
quint64 QSprkDescriptor::offset ()
{
    uint64_t rv = sprk_descriptor_offset (self);
    return rv;
}

///
//  
quint64 QSprkDescriptor::length ()
{
    uint64_t rv = sprk_descriptor_length (self);
    return rv;
}

///
//  
quint32 QSprkDescriptor::rowSize ()
{
    uint32_t rv = sprk_descriptor_row_size (self);
    return rv;
}

///
//  Self test of this class.
void QSprkDescriptor::test (bool verbose)
{
    sprk_descriptor_test (verbose);
    
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
