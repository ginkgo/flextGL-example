flextGL example
===============

This is a small example program that demonstrates how [flextGL](https://github.com/ginkgo/flextGL) can be included in your build system.

Cloning flextGL
---------------

flextGL is included as a Git submodule. To check it out call

    git submodule init
    git submodule update

This is necessary independent of which build system is going to be used.

Compilation
-----------

There are two separate build scripts available:

Make
----

This only works with Linux. You need to have GLFW3 installed.

Just call `make` to build the example program. 

You can find the build script in `Makefile`.

CMake
-----

This works both with Windows and Linux.

For building under Linux, call:

    mkdir build
    cd build
    cmake ..
    make

This should build the example in the separate build directory and copy all files necessary for execution in there.

For building with Windows and Visual Studio, the easiest way is to use cmake-gui. Select the path of the example
project. Select a build path and click on "Generate". This will let you select the compiler chain. There is currently only precompiled libraries for 32-bit Visual Studio 2008 and 2010 included.

After doing this, there will be a Visual Studio solution file in the build directory. Open it and build the contained `example` project.

You can find the build script in `CMakeLists.txt`
