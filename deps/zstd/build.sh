#!/bin/sh

set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../zstd/build/cmake
make -j4 install