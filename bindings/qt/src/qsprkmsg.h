/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
#ifndef Q_SPRK_MSG_H
#define Q_SPRK_MSG_H

#include "qsprk.h"

class QT_SPRK_EXPORT QSprkMsg : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QSprkMsg (sprk_msg_t *self, QObject *qObjParent = 0);

    //  Self test of this class.
    static void test (bool verbose);

    sprk_msg_t *self;
};
#endif //  Q_SPRK_MSG_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/