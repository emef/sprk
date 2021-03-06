/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#ifndef QML_SPRK_DESCRIPTOR_H
#define QML_SPRK_DESCRIPTOR_H

#include <QtQml>

#include <sprk.h>
#include "qml_sprk_plugin.h"


class QmlSprkDescriptor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNULL READ isNULL)
    
public:
    sprk_descriptor_t *self;
    
    QmlSprkDescriptor() { self = NULL; }
    bool isNULL() { return self == NULL; }
    
    static QObject* qmlAttachedProperties(QObject* object); // defined in QmlSprkDescriptor.cpp
    
public slots:
    //  
    const QString uri ();

    //  
    uint64_t offset ();

    //  
    uint64_t length ();

    //  
    uint32_t rowSize ();
};

class QmlSprkDescriptorAttached : public QObject
{
    Q_OBJECT
    QObject* m_attached;
    
public:
    QmlSprkDescriptorAttached (QObject* attached) {
        Q_UNUSED (attached);
    };
    
public slots:
    //  Self test of this class.
    void test (bool verbose);

    //  Creates a new descriptor.
    //  Creates a new descriptor.
    QmlSprkDescriptor *construct (const QString &uri, uint64_t offset, uint64_t length, uint32_t rowSize);

    //  Destroy the sprk_descriptor.
    void destruct (QmlSprkDescriptor *qmlSelf);
};


QML_DECLARE_TYPEINFO(QmlSprkDescriptor, QML_HAS_ATTACHED_PROPERTIES)

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
