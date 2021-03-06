/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
#ifndef Q_SPRK_TRANSFORM_H
#define Q_SPRK_TRANSFORM_H

#include "qsprk.h"

class QT_SPRK_EXPORT QSprkTransform : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QSprkTransform (sprk_transform_t *self, QObject *qObjParent = 0);

    //  Creates a new transformation.
    explicit QSprkTransform (QObject *qObjParent = 0);

    //  Destroy the sprk_transform.
    ~QSprkTransform ();

    //  Self test of this class.
    static void test (bool verbose);

    sprk_transform_t *self;
};
#endif //  Q_SPRK_TRANSFORM_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
