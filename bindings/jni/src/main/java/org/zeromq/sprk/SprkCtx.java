/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
package org.zeromq.sprk;

public class SprkCtx implements AutoCloseable{
    static {
        try {
            System.loadLibrary ("sprkjni");
        }
        catch (Exception e) {
            System.exit (-1);
        }
    }
    public long self;
    /*
    Creates a new sprk context which facilitates communication with
    known executors.                                               
    */
    native static long __new (String brokerUri);
    public SprkCtx (String brokerUri) {
        /*  TODO: if __new fails, self is null...            */
        self = __new (brokerUri);
    }
    public SprkCtx (long pointer) {
        self = pointer;
    }
    /*
    Destroy the sprk_ctx.
    */
    native static void __destroy (long self);
    @Override
    public void close () {
        __destroy (self);
        self = 0;
    }
    /*
    Loads data located in given paths distributed across executors.
    */
    native static long __loadDense (long self, String pathList, int rowSize);
    public SprkDataset loadDense (String pathList, int rowSize) {
        return new SprkDataset (__loadDense (self, pathList, rowSize));
    }
    /*
    Self test of this class.
    */
    native static void __test (boolean verbose);
    public static void test (boolean verbose) {
        __test (verbose);
    }
}
