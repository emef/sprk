/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
package org.zeromq.sprk;

import org.junit.Assert;
import org.junit.Test;

public class DescriptorTest {
    static {
        try {
            System.loadLibrary ("sprkjni");
        }
        catch (Exception e) {
            System.exit (-1);
        }
    }
    @Test
    public void test () {
        Descriptor.test (false);
    }
}
