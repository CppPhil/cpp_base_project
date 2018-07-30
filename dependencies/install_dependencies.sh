#!/bin/bash

delete_directory_if_exists () {
    if [ -d $1 ]; then
        rm -rf $1
    fi
}

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )


# Install philslib, expected-lite and brigand via git.
readonly GITHUB="https://github.com"
readonly LIB_PATH="$DIR/libraries"
readonly PHILSLIB_PATH="$LIB_PATH/philslib"
readonly EXPECTED_LITE_PATH="$LIB_PATH/expected-lite"
readonly BRIGAND_PATH="$LIB_PATH/brigand"

delete_directory_if_exists $PHILSLIB_PATH
delete_directory_if_exists $EXPECTED_LITE_PATH
delete_directory_if_exists $BRIGAND_PATH

git clone $GITHUB/CppPhil/philslib.git $PHILSLIB_PATH
git clone $GITHUB/martinmoene/expected-lite.git $EXPECTED_LITE_PATH
git clone $GITHUB/edouarda/brigand.git $BRIGAND_PATH


# Install vcpkg
readonly PACKAGE_MANAGER_PATH="$DIR/package_manager"
readonly VCPKG_PATH="$PACKAGE_MANAGER_PATH/vcpkg"
readonly VCPKG="$VCPKG_PATH/vcpkg"

delete_directory_if_exists $VCPKG_PATH

git clone $GITHUB/Microsoft/vcpkg $VCPKG_PATH
bash $VCPKG_PATH/bootstrap-vcpkg.sh
$VCPKG update
$VCPKG install boost
$VCPKG install ms-gsl
$VCPKG install doctest
$VCPKG install fmt

