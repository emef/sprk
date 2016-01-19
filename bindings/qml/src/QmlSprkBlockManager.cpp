/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "QmlSprkBlockManager.h"


///
//  
QmlSprkBlockdata *QmlSprkBlockManager::readAndStoreBlock (const QString &blockId, QmlSprkBlock *blockRef) {
    QmlSprkBlockdata *retQ_ = new QmlSprkBlockdata ();
    retQ_->self = sprk_block_manager_read_and_store_block (self, blockId.toUtf8().data(), &blockRef->self);
    return retQ_;
};

///
//  
QmlSprkBlockdata *QmlSprkBlockManager::getBlock (const QString &blockId) {
    QmlSprkBlockdata *retQ_ = new QmlSprkBlockdata ();
    retQ_->self = sprk_block_manager_get_block (self, blockId.toUtf8().data());
    return retQ_;
};


QObject* QmlSprkBlockManager::qmlAttachedProperties(QObject* object) {
    return new QmlSprkBlockManagerAttached(object);
}


///
//  Self test of this class.
void QmlSprkBlockManagerAttached::test (bool verbose) {
    sprk_block_manager_test (verbose);
};

///
//  Create a new block manager
QmlSprkBlockManager *QmlSprkBlockManagerAttached::construct () {
    QmlSprkBlockManager *qmlSelf = new QmlSprkBlockManager ();
    qmlSelf->self = sprk_block_manager_new ();
    return qmlSelf;
};

///
//  Destroy the block manager
void QmlSprkBlockManagerAttached::destruct (QmlSprkBlockManager *qmlSelf) {
    sprk_block_manager_destroy (&qmlSelf->self);
};

/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/