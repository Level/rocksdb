{
    "targets": [{
      "target_name": "leveldown"
    , "conditions": [
          ["OS == 'win'", {
              "defines": [
                  "_HAS_EXCEPTIONS=1"
                , "OS_WIN=1"
              ]
            , "msvs_settings": {
                  "VCCLCompilerTool": {
                      "RuntimeTypeInfo": "false"
                    , "EnableFunctionLevelLinking": "true"
                    , "ExceptionHandling": "2"
                    , "DisableSpecificWarnings": [ "4355", "4530" ,"4267", "4244", "4506" ]
                  }
              , 'VCLinkerTool': {
                    'AdditionalDependencies': [
                        # SDK import libs.
                        'Shlwapi.lib',
                        'rpcrt4.lib'
                    ]
                }
              }
          }, { # OS != 'win'
              'cflags!': [ '-fno-rtti' ]
            , 'cflags_cc!': [ '-fno-rtti' ]
            , 'cflags_cc+': [ '-frtti' ]
          }]
        , ["OS == 'mac'", {
            "cflags+": ["-fvisibility=hidden"],
            'xcode_settings': {
                  "GCC_SYMBOLS_PRIVATE_EXTERN": "YES" # -fvisibility=hidden
                , 'WARNING_CFLAGS': [
                    '-Wno-sign-compare'
                  , '-Wno-unused-variable'
                  , '-Wno-unused-function'
                  , '-Wno-ignored-qualifiers'
                ]
                , 'OTHER_CPLUSPLUSFLAGS': [
                    '-mmacosx-version-min=13.6'
                  , '-std=c++17'
                  , '-stdlib=libc++'
                  , '-arch arm64'
                ]
                , 'OTHER_LDFLAGS': [
                    '-stdlib=libc++'
                  , '-arch arm64'
                ]
                , 'GCC_ENABLE_CPP_RTTI': 'YES'
                , 'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                , 'MACOSX_DEPLOYMENT_TARGET': '13.6'
            }
          }]
        , ['OS == "linux"', {
              'cflags': ['-fPIC']
            , 'cflags!': [ '-fno-tree-vrp', '-fno-exceptions' ]
            , 'cflags_cc!': [ '-fno-exceptions' ]
          }, {
            'libraries!': [ "<(module_root_dir)/deps/aws-sdk-cpp/lib/libs2n.a" ]
          }]
        ]
      , "libraries": [
            "<(module_root_dir)/deps/zstd/lib/libzstd.a",
            "<(module_root_dir)/deps/rocksdb-cloud/lib/librocksdb.a",

            # aws-sdk-cpp
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-cpp-sdk-kinesis.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-cpp-sdk-s3.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-cpp-sdk-transfer.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-cpp-sdk-core.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-crt-cpp.a",

            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-s3.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-auth.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-http.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-compression.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-event-stream.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-io.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-cal.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-mqtt.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-sdkutils.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-c-common.a",

            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libs2n.a",
            "<(module_root_dir)/deps/aws-sdk-cpp/lib/libaws-checksums.a",

            "-lcurl"
        ]
      , "include_dirs"  : [
            "<(module_root_dir)/deps/aws-sdk-cpp/include",
            "<(module_root_dir)/deps/rocksdb-cloud/rocksdb-cloud/include",
            "<!(node -e \"require('napi-macros')\")"
        ]
      , "sources": [
            "binding.cc"
        ]
    }]
}
