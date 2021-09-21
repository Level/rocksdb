{
  'targets': [{
    'target_name': 'rocksdb'
  , 'type': 'static_library'
		# Overcomes an issue with the linker and thin .a files on SmartOS
  , 'standalone_static_library': 1
  , 'dependencies': [
        '../snappy/snappy.gyp:snappy'
    ]
  , 'direct_dependent_settings': {
        'include_dirs': [
            'rocksdb/include/'
        ]
    }
  , 'defines': [
        'SNAPPY=1'
    ]
  , 'include_dirs': [
        'rocksdb/'
      , 'rocksdb/include/'
    ]
  , 'conditions': [
        ['OS == "win"', {
            'include_dirs': [
                 'rocksdb/port/win/'
            ]
          , 'defines': [
                'LEVELDB_PLATFORM_UV=1'
              , 'OS_WIN=1'
              , 'NOMINMAX=1'
              , '_HAS_EXCEPTIONS=1'
            ]
          , 'sources': [
                'rocksdb/port/win/io_win.cc'
              , 'rocksdb/port/win/env_win.cc'
              , 'rocksdb/port/win/env_default.cc'
              , 'rocksdb/port/win/port_win.cc'
              , 'rocksdb/port/win/win_logger.cc'
              , 'rocksdb/port/win/win_thread.cc'
            ]
          , 'msvs_settings': {
                'VCCLCompilerTool': {
                    'EnableFunctionLevelLinking': 'true'
                  , 'ExceptionHandling': '2'
                  , 'DisableSpecificWarnings': [ '4355', '4530' ,'4267', '4244' ]
                }
            }
          # Must define RuntimeTypeInfo per configuration to override
          # the default setting (see nodejs/node-gyp#857 and #26).
          , 'configurations': {
                'Debug': {
                    'msvs_settings': {
                        'VCCLCompilerTool': {
                            'RuntimeTypeInfo': 'true'
                        }
                    }
                },
                'Release': {
                    'msvs_settings': {
                        'VCCLCompilerTool': {
                            'RuntimeTypeInfo': 'true'
                        }
                    }
                }
            }
        }, { # OS != "win"
            'sources': [
                'rocksdb/port/port_posix.cc'
              , 'rocksdb/env/env_posix.cc'
              , 'rocksdb/env/fs_posix.cc'
              , 'rocksdb/env/io_posix.cc'
            ]
          , 'defines': [
                'ROCKSDB_PLATFORM_POSIX=1'
            ]
          , 'ccflags': [
                '-fno-builtin-memcmp'
              , '-fPIC'
            ]
          , 'cflags': [ '-std=c++0x' ]
          , 'cflags!': [ '-fno-tree-vrp', '-fno-rtti' ]
          , 'cflags_cc!': [ '-fno-rtti' ]
          # , 'cflags_cc+': [ '-frtti' ]
        }]
      , ['OS != "win"' and 'OS != "freebsd"', {
            'cflags': [
                '-Wno-sign-compare'
              , '-Wno-unused-but-set-variable'
            ]
        }]
      , ['OS == "linux"', {
            'defines': [
                'OS_LINUX=1',
                'ROCKSDB_LIB_IO_POSIX=1'
            ]
          , 'libraries': [
                '-lpthread'
            ]
          , 'ccflags': [
                '-pthread'
                '-fexceptions'
            ]
          , 'cflags!': [ '-fno-exceptions' ]
          , 'cflags_cc!': [ '-fno-exceptions' ]
        }]
      , ['OS == "freebsd"', {
            'defines': [
                'OS_FREEBSD=1'
              , '_REENTRANT=1'
            ]
          , 'libraries': [
                '-lpthread'
            ]
          , 'ccflags': [
                '-pthread'
            ]
          , 'cflags': [
                '-Wno-sign-compare'
            ]
        }]
      , ['OS == "openbsd"', {
            'defines': [
                'OS_OPENBSD=1'
              , '_REENTRANT=1'
            ]
          , 'libraries': [
                '-lpthread'
            ]
          , 'ccflags': [
                '-pthread'
            ]
          , 'cflags': [
                '-Wno-sign-compare'
            ]
        }]
      , ['OS == "solaris"', {
            'defines': [
                'OS_SOLARIS=1'
              , '_REENTRANT=1'
            ]
          , 'libraries': [
                '-lrt'
              , '-lpthread'
            ]
          , 'ccflags': [
                '-pthread'
            ]
        }]
      , ['OS == "mac"', {
            'defines': [
                'OS_MACOSX=1',
                'ROCKSDB_LIB_IO_POSIX=1',
                'ROCKSDB_BACKTRACE=1'
            ]
          , 'libraries': []
          , 'ccflags': []
          , 'xcode_settings': {
                'WARNING_CFLAGS': [
                    '-Wno-sign-compare'
                  , '-Wno-unused-variable'
                  , '-Wno-unused-function'
                ]
                , 'OTHER_CPLUSPLUSFLAGS': [
                    '-mmacosx-version-min=10.8'
                  , '-std=c++11'
                  , '-stdlib=libc++'
                  , '-fno-omit-frame-pointer'
                  , '-momit-leaf-frame-pointer'
                ]
# , 'OTHER_LDFLAGS': ['-stdlib=libc++']
                , 'GCC_ENABLE_CPP_RTTI': 'YES'
                , 'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                , 'MACOSX_DEPLOYMENT_TARGET': '10.8'
            }
        }]
      , ['target_arch == "arm64" or target_arch == "aarch64"', {
          'sources': [
            'rocksdb/util/crc32c_arm64.cc'
          ]
        , 'ccflags': [
            '-march=armv8-a+crc+crypto'
          ]
        }]
    ]
  , 'sources': [
        'rocksdb/cache/cache.cc'
      , 'rocksdb/cache/clock_cache.cc'
      , 'rocksdb/cache/lru_cache.cc'
      , 'rocksdb/cache/sharded_cache.cc'
      , 'rocksdb/db/arena_wrapped_db_iter.cc'
      , 'rocksdb/db/blob/blob_file_addition.cc'
      , 'rocksdb/db/blob/blob_file_builder.cc'
      , 'rocksdb/db/blob/blob_file_cache.cc'
      , 'rocksdb/db/blob/blob_file_garbage.cc'
      , 'rocksdb/db/blob/blob_file_meta.cc'
      , 'rocksdb/db/blob/blob_file_reader.cc'
      , 'rocksdb/db/blob/blob_log_format.cc'
      , 'rocksdb/db/blob/blob_log_sequential_reader.cc'
      , 'rocksdb/db/blob/blob_log_writer.cc'
      , 'rocksdb/db/builder.cc'
      , 'rocksdb/db/c.cc'
      , 'rocksdb/db/column_family.cc'
      , 'rocksdb/db/compacted_db_impl.cc'
      , 'rocksdb/db/compaction/compaction.cc'
      , 'rocksdb/db/compaction/compaction_iterator.cc'
      , 'rocksdb/db/compaction/compaction_picker.cc'
      , 'rocksdb/db/compaction/compaction_job.cc'
      , 'rocksdb/db/compaction/compaction_picker_fifo.cc'
      , 'rocksdb/db/compaction/compaction_picker_level.cc'
      , 'rocksdb/db/compaction/compaction_picker_universal.cc'
      , 'rocksdb/db/compaction/sst_partitioner.cc'
      , 'rocksdb/db/convenience.cc'
      , 'rocksdb/db/db_filesnapshot.cc'
      , 'rocksdb/db/db_impl/db_impl.cc'
      , 'rocksdb/db/db_impl/db_impl_write.cc'
      , 'rocksdb/db/db_impl/db_impl_compaction_flush.cc'
      , 'rocksdb/db/db_impl/db_impl_files.cc'
      , 'rocksdb/db/db_impl/db_impl_open.cc'
      , 'rocksdb/db/db_impl/db_impl_debug.cc'
      , 'rocksdb/db/db_impl/db_impl_experimental.cc'
      , 'rocksdb/db/db_impl/db_impl_readonly.cc'
      , 'rocksdb/db/db_impl/db_impl_secondary.cc'
      , 'rocksdb/db/db_info_dumper.cc'
      , 'rocksdb/db/db_iter.cc'
      , 'rocksdb/db/dbformat.cc'
      , 'rocksdb/db/error_handler.cc'
      , 'rocksdb/db/event_helpers.cc'
      , 'rocksdb/db/experimental.cc'
      , 'rocksdb/db/external_sst_file_ingestion_job.cc'
      , 'rocksdb/db/file_indexer.cc'
      , 'rocksdb/db/flush_job.cc'
      , 'rocksdb/db/flush_scheduler.cc'
      , 'rocksdb/db/forward_iterator.cc'
      , 'rocksdb/db/import_column_family_job.cc'
      , 'rocksdb/db/internal_stats.cc'
      , 'rocksdb/db/logs_with_prep_tracker.cc'
      , 'rocksdb/db/log_reader.cc'
      , 'rocksdb/db/log_writer.cc'
      , 'rocksdb/db/malloc_stats.cc'
      , 'rocksdb/db/memtable.cc'
      , 'rocksdb/db/memtable_list.cc'
      , 'rocksdb/db/merge_helper.cc'
      , 'rocksdb/db/merge_operator.cc'
      , 'rocksdb/db/output_validator.cc'
      , 'rocksdb/db/periodic_work_scheduler.cc'
      , 'rocksdb/db/range_del_aggregator.cc'
      , 'rocksdb/db/range_tombstone_fragmenter.cc'
      , 'rocksdb/db/repair.cc'
      , 'rocksdb/db/snapshot_impl.cc'
      , 'rocksdb/db/table_cache.cc'
      , 'rocksdb/db/table_properties_collector.cc'
      , 'rocksdb/db/transaction_log_impl.cc'
      , 'rocksdb/db/trim_history_scheduler.cc'
      , 'rocksdb/db/version_builder.cc'
      , 'rocksdb/db/version_edit.cc'
      , 'rocksdb/db/version_edit_handler.cc'
      , 'rocksdb/db/version_set.cc'
      , 'rocksdb/db/wal_edit.cc'
      , 'rocksdb/db/wal_manager.cc'
      , 'rocksdb/db/write_batch.cc'
      , 'rocksdb/db/write_batch_base.cc'
      , 'rocksdb/db/write_controller.cc'
      , 'rocksdb/db/write_thread.cc'
      , 'rocksdb/env/env.cc'
      , 'rocksdb/env/env_chroot.cc'
      , 'rocksdb/env/env_encryption.cc'
      , 'rocksdb/env/env_hdfs.cc'
      , 'rocksdb/env/file_system.cc'
      , 'rocksdb/env/file_system_tracer.cc'
      , 'rocksdb/env/mock_env.cc'
      , 'rocksdb/file/delete_scheduler.cc'
      , 'rocksdb/file/file_prefetch_buffer.cc'
      , 'rocksdb/file/file_util.cc'
      , 'rocksdb/file/filename.cc'
      , 'rocksdb/file/random_access_file_reader.cc'
      , 'rocksdb/file/read_write_util.cc'
      , 'rocksdb/file/readahead_raf.cc'
      , 'rocksdb/file/sequence_file_reader.cc'
      , 'rocksdb/file/sst_file_manager_impl.cc'
      , 'rocksdb/file/writable_file_writer.cc'
      , 'rocksdb/logging/auto_roll_logger.cc'
      , 'rocksdb/logging/event_logger.cc'
      , 'rocksdb/logging/log_buffer.cc'
      , 'rocksdb/memory/arena.cc'
      , 'rocksdb/memory/concurrent_arena.cc'
      , 'rocksdb/memory/jemalloc_nodump_allocator.cc'
      , 'rocksdb/memtable/alloc_tracker.cc'
      , 'rocksdb/memtable/hash_linklist_rep.cc'
      , 'rocksdb/memtable/hash_skiplist_rep.cc'
      , 'rocksdb/memtable/skiplistrep.cc'
      , 'rocksdb/memtable/vectorrep.cc'
      , 'rocksdb/memtable/write_buffer_manager.cc'
      , 'rocksdb/monitoring/histogram.cc'
      , 'rocksdb/monitoring/histogram_windowing.cc'
      , 'rocksdb/monitoring/in_memory_stats_history.cc'
      , 'rocksdb/monitoring/instrumented_mutex.cc'
      , 'rocksdb/monitoring/iostats_context.cc'
      , 'rocksdb/monitoring/perf_context.cc'
      , 'rocksdb/monitoring/perf_level.cc'
      , 'rocksdb/monitoring/persistent_stats_history.cc'
      , 'rocksdb/monitoring/statistics.cc'
      , 'rocksdb/monitoring/thread_status_impl.cc'
      , 'rocksdb/monitoring/thread_status_updater.cc'
      , 'rocksdb/monitoring/thread_status_util.cc'
      , 'rocksdb/monitoring/thread_status_util_debug.cc'
      , 'rocksdb/options/cf_options.cc'
      , 'rocksdb/options/configurable.cc'
      , 'rocksdb/options/customizable.cc'
      , 'rocksdb/options/db_options.cc'
      , 'rocksdb/options/options.cc'
      , 'rocksdb/options/options_helper.cc'
      , 'rocksdb/options/options_parser.cc'
      , 'rocksdb/port/stack_trace.cc'
      , 'rocksdb/table/adaptive/adaptive_table_factory.cc'
      , 'rocksdb/table/block_based/binary_search_index_reader.cc'
      , 'rocksdb/table/block_based/block.cc'
      , 'rocksdb/table/block_based/block_based_filter_block.cc'
      , 'rocksdb/table/block_based/block_based_table_builder.cc'
      , 'rocksdb/table/block_based/block_based_table_factory.cc'
      , 'rocksdb/table/block_based/block_based_table_iterator.cc'
      , 'rocksdb/table/block_based/block_based_table_reader.cc'
      , 'rocksdb/table/block_based/block_builder.cc'
      , 'rocksdb/table/block_based/block_prefetcher.cc'
      , 'rocksdb/table/block_based/block_prefix_index.cc'
      , 'rocksdb/table/block_based/data_block_hash_index.cc'
      , 'rocksdb/table/block_based/data_block_footer.cc'
      , 'rocksdb/table/block_based/filter_block_reader_common.cc'
      , 'rocksdb/table/block_based/filter_policy.cc'
      , 'rocksdb/table/block_based/flush_block_policy.cc'
      , 'rocksdb/table/block_based/full_filter_block.cc'
      , 'rocksdb/table/block_based/hash_index_reader.cc'
      , 'rocksdb/table/block_based/index_builder.cc'
      , 'rocksdb/table/block_based/index_reader_common.cc'
      , 'rocksdb/table/block_based/parsed_full_filter_block.cc'
      , 'rocksdb/table/block_based/partitioned_filter_block.cc'
      , 'rocksdb/table/block_based/partitioned_index_iterator.cc'
      , 'rocksdb/table/block_based/partitioned_index_reader.cc'
      , 'rocksdb/table/block_based/reader_common.cc'
      , 'rocksdb/table/block_based/uncompression_dict_reader.cc'
      , 'rocksdb/table/block_fetcher.cc'
      , 'rocksdb/table/cuckoo/cuckoo_table_builder.cc'
      , 'rocksdb/table/cuckoo/cuckoo_table_factory.cc'
      , 'rocksdb/table/cuckoo/cuckoo_table_reader.cc'
      , 'rocksdb/table/format.cc'
      , 'rocksdb/table/get_context.cc'
      , 'rocksdb/table/iterator.cc'
      , 'rocksdb/table/merging_iterator.cc'
      , 'rocksdb/table/meta_blocks.cc'
      , 'rocksdb/table/persistent_cache_helper.cc'
      , 'rocksdb/table/plain/plain_table_bloom.cc'
      , 'rocksdb/table/plain/plain_table_builder.cc'
      , 'rocksdb/table/plain/plain_table_factory.cc'
      , 'rocksdb/table/plain/plain_table_index.cc'
      , 'rocksdb/table/plain/plain_table_key_coding.cc'
      , 'rocksdb/table/plain/plain_table_reader.cc'
      , 'rocksdb/table/sst_file_dumper.cc'
      , 'rocksdb/table/sst_file_reader.cc'
      , 'rocksdb/table/sst_file_writer.cc'
      , 'rocksdb/table/table_factory.cc'
      , 'rocksdb/table/table_properties.cc'
      , 'rocksdb/table/two_level_iterator.cc'
      , 'rocksdb/test_util/sync_point.cc'
      , 'rocksdb/test_util/sync_point_impl.cc'
      , 'rocksdb/test_util/testutil.cc'
      , 'rocksdb/test_util/transaction_test_util.cc'
      , 'rocksdb/tools/block_cache_analyzer/block_cache_trace_analyzer.cc'

      # Optional (WITH_BENCHMARK_TOOLS)
      # , 'rocksdb/tools/db_bench.cc'
      # , 'rocksdb/tools/db_bench_tool.cc'

      , 'rocksdb/tools/dump/db_dump_tool.cc'
      , 'rocksdb/tools/io_tracer_parser_tool.cc'
      , 'rocksdb/tools/ldb_cmd.cc'
      , 'rocksdb/tools/ldb_tool.cc'
      , 'rocksdb/tools/sst_dump_tool.cc'
      , 'rocksdb/tools/trace_analyzer_tool.cc'
      , 'rocksdb/trace_replay/trace_replay.cc'
      , 'rocksdb/trace_replay/block_cache_tracer.cc'
      , 'rocksdb/trace_replay/io_tracer.cc'
      , 'rocksdb/util/coding.cc'
      , 'rocksdb/util/compaction_job_stats_impl.cc'
      , 'rocksdb/util/comparator.cc'
      , 'rocksdb/util/compression_context_cache.cc'
      , 'rocksdb/util/concurrent_task_limiter_impl.cc'
      , 'rocksdb/util/crc32c.cc'
      , 'rocksdb/util/dynamic_bloom.cc'
      , 'rocksdb/util/hash.cc'
      , 'rocksdb/util/murmurhash.cc'
      , 'rocksdb/util/random.cc'
      , 'rocksdb/util/rate_limiter.cc'
      , 'rocksdb/util/slice.cc'
      , 'rocksdb/util/file_checksum_helper.cc'
      , 'rocksdb/util/status.cc'
      , 'rocksdb/util/string_util.cc'
      , 'rocksdb/util/thread_local.cc'
      , 'rocksdb/util/threadpool_imp.cc'
      , 'rocksdb/util/xxhash.cc'

      # Unused
      # , 'rocksdb/utilities/backupable/backupable_db.cc'

      # Unused
      # , 'rocksdb/utilities/blob_db/blob_compaction_filter.cc'
      # , 'rocksdb/utilities/blob_db/blob_db.cc'
      # , 'rocksdb/utilities/blob_db/blob_db_impl.cc'
      # , 'rocksdb/utilities/blob_db/blob_db_impl_filesnapshot.cc'
      # , 'rocksdb/utilities/blob_db/blob_dump_tool.cc'
      # , 'rocksdb/utilities/blob_db/blob_file.cc'

      # Unused
      # , 'rocksdb/utilities/cassandra/cassandra_compaction_filter.cc'
      # , 'rocksdb/utilities/cassandra/format.cc'
      # , 'rocksdb/utilities/cassandra/merge_operator.cc'

      , 'rocksdb/utilities/checkpoint/checkpoint_impl.cc'
      , 'rocksdb/utilities/compaction_filters/remove_emptyvalue_compactionfilter.cc'
      , 'rocksdb/utilities/debug.cc'

      # Unused
      # , 'rocksdb/utilities/env_mirror.cc'
      # , 'rocksdb/utilities/env_timed.cc'

      # Unused
      # , 'rocksdb/utilities/fault_injection_env.cc'
      # , 'rocksdb/utilities/fault_injection_fs.cc'

      , 'rocksdb/utilities/leveldb_options/leveldb_options.cc'
      , 'rocksdb/utilities/memory/memory_util.cc'

      # Unused
      # , 'rocksdb/utilities/merge_operators/bytesxor.cc'
      # , 'rocksdb/utilities/merge_operators/max.cc'
      # , 'rocksdb/utilities/merge_operators/put.cc'
      # , 'rocksdb/utilities/merge_operators/sortlist.cc'
      # , 'rocksdb/utilities/merge_operators/string_append/stringappend.cc'
      # , 'rocksdb/utilities/merge_operators/string_append/stringappend2.cc'
      # , 'rocksdb/utilities/merge_operators/uint64add.cc'

      , 'rocksdb/utilities/object_registry.cc'
      , 'rocksdb/utilities/option_change_migration/option_change_migration.cc'
      , 'rocksdb/utilities/options/options_util.cc'

      # Unused
      # , 'rocksdb/utilities/persistent_cache/block_cache_tier.cc'
      # , 'rocksdb/utilities/persistent_cache/block_cache_tier_file.cc'
      # , 'rocksdb/utilities/persistent_cache/block_cache_tier_metadata.cc'
      # , 'rocksdb/utilities/persistent_cache/persistent_cache_tier.cc'
      # , 'rocksdb/utilities/persistent_cache/volatile_tier_impl.cc'

      # Unused
      # , 'rocksdb/utilities/simulator_cache/cache_simulator.cc'
      # , 'rocksdb/utilities/simulator_cache/sim_cache.cc'

      , 'rocksdb/utilities/table_properties_collectors/compact_on_deletion_collector.cc'
      , 'rocksdb/utilities/trace/file_trace_reader_writer.cc'
      , 'rocksdb/utilities/transactions/lock/lock_manager.cc'
      , 'rocksdb/utilities/transactions/lock/point/point_lock_tracker.cc'
      , 'rocksdb/utilities/transactions/lock/point/point_lock_manager.cc'
      , 'rocksdb/utilities/transactions/lock/range/range_tree/range_tree_lock_manager.cc'
      , 'rocksdb/utilities/transactions/lock/range/range_tree/range_tree_lock_tracker.cc'
      , 'rocksdb/utilities/transactions/optimistic_transaction_db_impl.cc'
      , 'rocksdb/utilities/transactions/optimistic_transaction.cc'
      , 'rocksdb/utilities/transactions/pessimistic_transaction.cc'
      , 'rocksdb/utilities/transactions/pessimistic_transaction_db.cc'
      , 'rocksdb/utilities/transactions/snapshot_checker.cc'
      , 'rocksdb/utilities/transactions/transaction_base.cc'
      , 'rocksdb/utilities/transactions/transaction_db_mutex_impl.cc'
      , 'rocksdb/utilities/transactions/transaction_util.cc'
      , 'rocksdb/utilities/transactions/write_prepared_txn.cc'
      , 'rocksdb/utilities/transactions/write_prepared_txn_db.cc'
      , 'rocksdb/utilities/transactions/write_unprepared_txn.cc'
      , 'rocksdb/utilities/transactions/write_unprepared_txn_db.cc'
      , 'rocksdb/utilities/ttl/db_ttl_impl.cc'
      , 'rocksdb/utilities/write_batch_with_index/write_batch_with_index.cc'
      , 'rocksdb/utilities/write_batch_with_index/write_batch_with_index_internal.cc'

      , 'build_version.cc'
    ]
}]}
