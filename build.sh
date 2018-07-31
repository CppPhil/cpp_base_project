#!/bin/bash

# The C compiler to use
readonly C_COMPILER="gcc-7"

# The C++ compiler to use
readonly CXX_COMPILER="g++-7"

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly VCPKG_CMAKE="${DIR}/deps/package_manager/vcpkg/scripts/buildsystems/vcpkg.cmake"

if [ "$#" -ne 1 ]; then
    echo "Illegal number of command line arguments. Enter Debug or Release as the first command line argument."
    exit 1
fi

if [ "$1" == "Debug" ] || [ "$1" == "Release" ] ; then
    CC=$C_COMPILER CXX=$CXX_COMPILER cmake -DCMAKE_TOOLCHAIN_FILE=$VCPKG_CMAKE -DCMAKE_BUILD_TYPE=$1 $DIR/
    cmake --build $DIR -- -j2
    exit 0
fi

echo "The first command line argument was neither Debug nor Release."
exit 1

