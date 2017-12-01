#!/bin/sh

# generate GL3W if needed
if ! [ -f "lib/gl3w/src/gl3w.c" ]; then
  pushd lib/gl3w
  ./gl3w_gen.py
  popd
fi

build='Release'
if [ "$1" == "debug" ]; then
  build='Debug'
fi

if ! [ -d "build/osx" ]; then
  mkdir -p "build/osx"
fi
cd build/osx

# C and C++ compiler
export CC="clang"
export CXX="clang++"

msg=" --------------------- Build Succeeded ---------------------"

# Generate build system using the "XCode" or "Unix Makefiles" generator.
# cmake -G "Xcode" \
cmake -G "Unix Makefiles" \
    -DBUILD_OSX=TRUE \
    -DCMAKE_BUILD_TYPE=$build \
    ../..

# Build and install the project using the Release config
cmake --build . --target all --config $build && echo $msg && pushd bin > /dev/null; run-tests "$2"; popd > /dev/null
