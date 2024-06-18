{
    "targets": [{
        "target_name": "aws-sdk-cpp",
        "type": "none",
        "actions": [{
            "action_name": "run build sh",
            "inputs": [],
            "outputs": [
                "lib/libaws-cpp-sdk-core",
                "lib/libaws-cpp-sdk-s3",
                "lib/libaws-cpp-sdk-kinesis",
                "lib/libaws-cpp-sdk-transfer"
            ],
            "action": [ "sh", "build.sh" ],
            "message": "Building aws-sdk-cpp"
        }]
    }]
}