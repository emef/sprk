/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#ifndef QML_SPRK_MSG_H
#define QML_SPRK_MSG_H

#include <QtQml>

#include <sprk.h>
#include "qml_sprk_plugin.h"


class QmlSprkMsg : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNULL READ isNULL)
    
public:
    sprk_msg_t *self;
    
    QmlSprkMsg() { self = NULL; }
    bool isNULL() { return self == NULL; }
    
    static QObject* qmlAttachedProperties(QObject* object); // defined in QmlSprkMsg.cpp
    
public slots:};

class QmlSprkMsgAttached : public QObject
{
    Q_OBJECT
    QObject* m_attached;
    
public:
    QmlSprkMsgAttached (QObject* attached) {
        Q_UNUSED (attached);
    };
    
public slots:
    //  Self test of this class.
    void test (bool verbose);
};


QML_DECLARE_TYPEINFO(QmlSprkMsg, QML_HAS_ATTACHED_PROPERTIES)

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
