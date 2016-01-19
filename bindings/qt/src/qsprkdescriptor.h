/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
#ifndef Q_SPRK_DESCRIPTOR_H
#define Q_SPRK_DESCRIPTOR_H

#include "qsprk.h"

class QT_SPRK_EXPORT QSprkDescriptor : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QSprkDescriptor (sprk_descriptor_t *self, QObject *qObjParent = 0);

    //  Creates a new descriptor.
    explicit QSprkDescriptor (QObject *qObjParent = 0);

    //  Destroy the sprk_descriptor.
    ~QSprkDescriptor ();

    //  Self test of this class.
    static void test (bool verbose);

    sprk_descriptor_t *self;
};
#endif //  Q_SPRK_DESCRIPTOR_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
