#!/bin/bash

### This script is used to run clang-format on the source files.

# Directory containing this bash script.
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Format the source files.
cd $DIR/src
bash $DIR/deps/clang-format/fmt.sh

cd $DIR/include
bash $DIR/deps/clang-format/fmt.sh

cd $DIR/test
bash $DIR/deps/clang-format/fmt.sh

