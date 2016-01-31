# sprk-jni

JNI Binding for sprk

## Building the JNI Layer for Linux

Ensure you have cmake installed, then run:

    ./gradle build jar
    ./gradle test

This calls javah to build the headers in src/native/c, and then compiles the C and Java pieces to create a jar file a sharable library (.so).

## Building the JNI Layer for Android

See bindings/jni/android/build.sh.

You need the Android Native Development Kit (NDK) installed.

Set these environment variables, e.g:

    ANDROID_NDK_ROOT=$HOME/android-ndk-r10e
    TOOLCHAIN_NAME=arm-linux-androideabi-4.9
    TOOLCHAIN_HOST=arm-linux-androideabi
    TOOLCHAIN_ARCH=arm
    TOOLCHAIN_PATH=$ANDROID_NDK_ROOT/toolchains/$TOOLCHAIN_NAME/prebuilt/linux-x86_64/bin

Then in the android directory, run:

    ./build.sh

This does the following:

* It compiles the sprk C sources for Android, into a native library libsprk.so in builds/android/
* It compiles the JNI Java classes into a jar file sprk-jni-0.0.0.jar in bindings/jni/build/libs
* It compiles the JNI C sources for Android, into a native library libsprkjni.so.
* It combines all these into sprk-android.jar, which you can use in your Android projects.

## Building the JNI Layer for Windows

You need MS Visual Studio 2010 or later.

You need the Java SDK. Set the JAVA_HOME environment to the installation location, e.g. C:Program FilesJavajdk1.8.0_66.

1. Check out all dependent projects from github, at the same level as this project. E.g.: libsodium, libzmq, czmq.
2. In each project, open a console in builds/msvc/vs2010 and run the build.bat batch file.
3. In this project, open a console in bindings/jni/msvc/vs2010 and run the build.bat batch file.

The resulting libraries (sprkjni.dll, sprkjni.lib) are created in bindings/jni/msvc/bin.

## Using the JNI API

- to be written.

## License


The MIT License (MIT)

Copyright (c) 2016 Matt Forbes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

