### AWS sdk cpp 빌드
```
git submodule update --init --recursive
cd deps/aws-sdk-cpp
mkdir -p build
cd build
cmake -DBUILD_ONLY="s3;kinesis;core;transfer" -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../aws-sdk-cpp/
make -j8 install
```

### zstd 빌드
```
git submodule update --init --recursive
cd deps/zstd
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ../zstd/build/cmake
make -j8 install
```

### RocksDB-cloud 빌드
```
cd deps/rocksdb-cloud
mkdir -p lib

cd rocksdb-cloud

CFLAGS='-I./../../zstd/include -I./../../aws-sdk-cpp/include -DUSE_AWS ' \
    CXXFLAGS='-I./../../zstd/include -I./../../aws-sdk-cpp/include -DUSE_AWS' \
    PLATFORM_LDFLAGS='-laws-cpp-sdk-s3 -laws-cpp-sdk-kinesis -laws-cpp-sdk-core -laws-cpp-sdk-transfer' \
    EXTRA_CFLAGS='-Wno-format -Wno-unused-variable' \
    EXTRA_CXXFLAGS='-Wno-format -Wno-unused-variable' \
    USE_RTTI=1 make -j8 static_lib

strip librocksdb.a
mv librocksdb.a ../lib/
```
