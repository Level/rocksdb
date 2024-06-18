{
    "targets": [{
        "target_name": "zstd",
        "type": "none",
        "actions": [{
            "action_name": "run build sh",
            "inputs": [ "zstd" ],
            "outputs": [ "lib/libzstd.a" ],
            "action": [ "bash", "build.sh" ],
            "message": "Building zstd"
        }],
    }]
}