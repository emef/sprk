/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
#ifndef Q_SPRK_DATASET_H
#define Q_SPRK_DATASET_H

#include "qsprk.h"

class QT_SPRK_EXPORT QSprkDataset : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QSprkDataset (sprk_dataset_t *self, QObject *qObjParent = 0);

    //  Creates a new sprk dataset from a set of input paths.
    explicit QSprkDataset (QSprkCtx *context, const QString &pathList, QObject *qObjParent = 0);

    //  Destroy the sprk_dataset.
    ~QSprkDataset ();

    //  Checkpoints all blocks and their transformations across executors.
    void checkpoint ();

    //  Multiplies all values by the multiplier.
    void mul (float multiplier);

    //  Calculates the sum of all values in the dataset.
    float sum ();

    //  Self test of this class.
    static void test (bool verbose);

    sprk_dataset_t *self;
};
#endif //  Q_SPRK_DATASET_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
