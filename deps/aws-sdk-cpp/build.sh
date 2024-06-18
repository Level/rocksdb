#!/bin/sh

mkdir -p build
cd build

cmake -DBUILD_ONLY="s3;kinesis;core;transfer" -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../aws-sdk-cpp/
make -j4 install
