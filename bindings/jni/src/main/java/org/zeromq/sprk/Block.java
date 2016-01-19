/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
package org.zeromq.sprk;

public class Block implements AutoCloseable{
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
    Creates a new block
    */
    native static long __new (long descriptor, long transformations);
    public Block (Descriptor descriptor, Transformation transformations) {
        /*  TODO: if __new fails, self is null...            */
        self = __new (descriptor.self, transformations.self);
    }
    public Block (long pointer) {
        self = pointer;
    }
    /*
    Destroy the block.
    */
    native static void __destroy (long self);
    @Override
    public void close () {
        __destroy (self);
        self = 0;
    }
    /*
    Self test of this class.
    */
    native static void __test (boolean verbose);
    public static void test (boolean verbose) {
        __test (verbose);
    }
}
