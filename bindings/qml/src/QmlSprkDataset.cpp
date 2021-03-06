/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "QmlSprkDataset.h"


///
//  Checkpoints all blocks and their transformations across executors.
void QmlSprkDataset::checkpoint () {
    sprk_dataset_checkpoint (self);
};

///
//  Multiplies all values by the multiplier.
void QmlSprkDataset::mul (float multiplier) {
    sprk_dataset_mul (self, multiplier);
};

///
//  Calculates the sum of all values in the dataset.
float QmlSprkDataset::sum () {
    return sprk_dataset_sum (self);
};


QObject* QmlSprkDataset::qmlAttachedProperties(QObject* object) {
    return new QmlSprkDatasetAttached(object);
}


///
//  Self test of this class.
void QmlSprkDatasetAttached::test (bool verbose) {
    sprk_dataset_test (verbose);
};

///
//  Destroy the sprk_dataset.
void QmlSprkDatasetAttached::destruct (QmlSprkDataset *qmlSelf) {
    sprk_dataset_destroy (&qmlSelf->self);
};

/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
