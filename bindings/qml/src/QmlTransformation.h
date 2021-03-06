/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#ifndef QML_TRANSFORMATION_H
#define QML_TRANSFORMATION_H

#include <QtQml>

#include <sprk.h>
#include "qml_sprk_plugin.h"


class QmlTransformation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNULL READ isNULL)
    
public:
    transformation_t *self;
    
    QmlTransformation() { self = NULL; }
    bool isNULL() { return self == NULL; }
    
    static QObject* qmlAttachedProperties(QObject* object); // defined in QmlTransformation.cpp
    
public slots:};

class QmlTransformationAttached : public QObject
{
    Q_OBJECT
    QObject* m_attached;
    
public:
    QmlTransformationAttached (QObject* attached) {
        Q_UNUSED (attached);
    };
    
public slots:
    //  Self test of this class.
    void test (bool verbose);

    //  Creates a new transformation.
    QmlTransformation *construct ();

    //  Destroy the transformation.
    void destruct (QmlTransformation *qmlSelf);
};


QML_DECLARE_TYPEINFO(QmlTransformation, QML_HAS_ATTACHED_PROPERTIES)

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
