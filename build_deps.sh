#!/bin/bash -e

# Fetch submodules
git submodule update --init --recursive

# Build dependencies
mkdir -p deps/aws-sdk-cpp/build
pushd deps/aws-sdk-cpp/build
cmake -DBUILD_ONLY="s3;kinesis;core;transfer" -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../aws-sdk-cpp/
make -j8 install
popd

mkdir -p deps/zstd/build
pushd deps/zstd/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../zstd/build/cmake
make -j8 install
popd

mkdir -p deps/rocksdb-cloud/lib
pushd deps/rocksdb-cloud/rocksdb-cloud
CFLAGS='-I./../../zstd/include -I./../../aws-sdk-cpp/include -DUSE_AWS ' \
    CXXFLAGS='-I./../../zstd/include -I./../../aws-sdk-cpp/include -DUSE_AWS' \
    PLATFORM_LDFLAGS='-laws-cpp-sdk-s3 -laws-cpp-sdk-kinesis -laws-cpp-sdk-core -laws-cpp-sdk-transfer' \
    EXTRA_CFLAGS='-Wno-format -Wno-unused-variable' \
    EXTRA_CXXFLAGS='-Wno-format -Wno-unused-variable' \
    USE_RTTI=1 make -j8 static_lib
mv librocksdb.a ../lib/
popd
