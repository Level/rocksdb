{
    "targets": [{
        "target_name": "rocksdb-cloud",
        "type": "none",
        "actions": [{
            "action_name": "run build.sh",
            "inputs": [ "rocksdb-cloud" ],
            "outputs": [ "lib/librocksdb.a" ],
            "action": [ "sh", "build.sh" ],
            "message": "Building rocksdb-cloud"
        }],
        "dependencies": [
            "../aws-sdk-cpp/aws-sdk-cpp.gyp:aws-sdk-cpp",
            "../zstd/zstd.gyp:zstd",
        ]
    }]
}