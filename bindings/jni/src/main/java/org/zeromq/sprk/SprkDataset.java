/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
package org.zeromq.sprk;

public class SprkDataset {
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
    Destroy the sprk_dataset.
    */
    native static void __destroy (long self);
    @Override
    public void close () {
        __destroy (self);
        self = 0;
    }
    /*
    Checkpoints all blocks and their transformations across executors.
    */
    native static void __checkpoint (long self);
    public void checkpoint () {
        __checkpoint (self);
    }
    /*
    Multiplies all values by the multiplier.
    */
    native static void __mul (long self, float multiplier);
    public void mul (float multiplier) {
        __mul (self, multiplier);
    }
    /*
    Calculates the sum of all values in the dataset.
    */
    native static float __sum (long self);
    public float sum () {
        return __sum (self);
    }
    /*
    Self test of this class.
    */
    native static void __test (boolean verbose);
    public static void test (boolean verbose) {
        __test (verbose);
    }
}
