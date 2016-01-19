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
    native static long __new ();
    public SprkCtx () {
        /*  TODO: if __new fails, self is null...            */
        self = __new ();
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
    Assign a block to the executor pool.
    */
    native static void __assignBlock (long self, long block);
    public void assignBlock (SprkBlock block) {
        __assignBlock (self, block.self);
    }
    /*
    Remove a block from the executor pool.
    */
    native static void __dropBlock (long self, long block);
    public void dropBlock (SprkBlock block) {
        __dropBlock (self, block.self);
    }
    /*
    Self test of this class.
    */
    native static void __test (boolean verbose);
    public static void test (boolean verbose) {
        __test (verbose);
    }
}
