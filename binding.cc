#define NAPI_VERSION 8

#include <napi-macros.h>
#include <node_api.h>
#include <assert.h>

#include <rocksdb/db.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/cache.h>
#include <rocksdb/filter_policy.h>
#include <rocksdb/cache.h>
#include <rocksdb/comparator.h>
#include <rocksdb/env.h>
#include <rocksdb/options.h>
#include <rocksdb/table.h>

namespace leveldb = rocksdb;

#include <set>
#include <optional>
#include <vector>

class NullLogger : public rocksdb::Logger {
public:
  using rocksdb::Logger::Logv;
  virtual void Logv(const char* format, va_list ap) override {}
  virtual size_t GetLogFileSize() const override { return 0; }
};

struct Database;
struct Iterator;
static void iterator_do_close (napi_env env, Iterator* iterator, napi_value cb);

#define NAPI_DB_CONTEXT() \
  Database* database = nullptr; \
  NAPI_STATUS_THROWS(napi_get_value_external(env, argv[0], (void**)&database));

#define NAPI_ITERATOR_CONTEXT() \
  Iterator* iterator = nullptr; \
  NAPI_STATUS_THROWS(napi_get_value_external(env, argv[0], (void**)&iterator));

#define NAPI_BATCH_CONTEXT() \
  leveldb::WriteBatch* batch = nullptr; \
  NAPI_STATUS_THROWS(napi_get_value_external(env, argv[0], (void**)&batch));

static bool IsString (napi_env env, napi_value value) {
  napi_valuetype type;
  napi_typeof(env, value, &type);
  return type == napi_string;
}

static bool IsBuffer (napi_env env, napi_value value) {
  bool isBuffer;
  napi_is_buffer(env, value, &isBuffer);
  return isBuffer;
}

static bool IsObject (napi_env env, napi_value value) {
  napi_valuetype type;
  napi_typeof(env, value, &type);
  return type == napi_object;
}

static napi_value CreateError (napi_env env, const std::string& str) {
  napi_value msg;
  napi_create_string_utf8(env, str.c_str(), str.size(), &msg);
  napi_value error;
  napi_create_error(env, nullptr, msg, &error);
  return error;
}

static bool HasProperty (napi_env env, napi_value obj, const char* key) {
  bool has = false;
  napi_has_named_property(env, obj, key, &has);
  return has;
}

static napi_value GetProperty (napi_env env, napi_value obj, const char* key) {
  napi_value value;
  napi_get_named_property(env, obj, key, &value);
  return value;
}

static bool BooleanProperty (napi_env env, napi_value obj, const char* key,
                             bool defaultValue) {
  if (HasProperty(env, obj, key)) {
    const auto value = GetProperty(env, obj, key);
    bool result;
    napi_get_value_bool(env, value, &result);
    return result;
  }

  return defaultValue;
}

static uint32_t Uint32Property (napi_env env, napi_value obj, const char* key,
                                uint32_t defaultValue) {
  if (HasProperty(env, obj, key)) {
    const auto value = GetProperty(env, obj, key);
    uint32_t result;
    napi_get_value_uint32(env, value, &result);
    return result;
  }

  return defaultValue;
}

static int Int32Property (napi_env env, napi_value obj, const char* key,
                          int defaultValue) {
  if (HasProperty(env, obj, key)) {
    const auto value = GetProperty(env, obj, key);
    int result;
    napi_get_value_int32(env, value, &result);
    return result;
  }

  return defaultValue;
}

static std::string ToString (napi_env env, napi_value from) {
  if (IsString(env, from)) {
    size_t length = 0;
    napi_get_value_string_utf8(env, from, nullptr, 0, &length);
    std::string value(length, '\0');
    napi_get_value_string_utf8( env, from, &value[0], value.length() + 1, &length);
    return value;
  } else if (IsBuffer(env, from)) {
    char* buf = nullptr;
    size_t length = 0;
    napi_get_buffer_info(env, from, reinterpret_cast<void **>(&buf), &length);
    return std::string(buf, length);
  }

  return {};
}

static std::string StringProperty (napi_env env, napi_value obj, const char* key) {
  if (HasProperty(env, obj, key)) {
    napi_value value = GetProperty(env, obj, key);
    if (IsString(env, value)) {
      return ToString(env, value);
    }
  }

  return "";
}

static size_t StringOrBufferLength (napi_env env, napi_value value) {
  size_t size = 0;

  if (IsString(env, value)) {
    napi_get_value_string_utf8(env, value, nullptr, 0, &size);
  } else if (IsBuffer(env, value)) {
    char* buf = nullptr;
    napi_get_buffer_info(env, value, (void **)&buf, &size);
  }

  return size;
}

static std::optional<std::string> RangeOption (napi_env env, napi_value opts, const char* name) {
  if (HasProperty(env, opts, name)) {
    const auto value = GetProperty(env, opts, name);

    if (StringOrBufferLength(env, value) > 0) {
      return ToString(env, value);
    }
  }

  return {};
}

static std::vector<std::string> KeyArray (napi_env env, napi_value arr) {
  uint32_t length;
  std::vector<std::string> result;

  if (napi_get_array_length(env, arr, &length) == napi_ok) {
    result.reserve(length);

    for (uint32_t i = 0; i < length; i++) {
      napi_value element;

      if (napi_get_element(env, arr, i, &element) == napi_ok &&
          StringOrBufferLength(env, element) > 0) {
        result.push_back(ToString(env, element));
      }
    }
  }

  return result;
}

static napi_status CallFunction (napi_env env,
                                 napi_value callback,
                                 const int argc,
                                 napi_value* argv) {
  napi_value global;
  napi_get_global(env, &global);
  return napi_call_function(env, global, callback, argc, argv, nullptr);
}

void Convert (napi_env env, const std::optional<std::string>& s, bool asBuffer, napi_value& result) {
  if (!s) {
    napi_get_undefined(env, &result);
  } else if (asBuffer) {
    napi_create_buffer_copy(env, s->size(), s->data(), nullptr, &result);
  } else {
    napi_create_string_utf8(env, s->data(), s->size(), &result);
  }
}

/**
 * Base worker class. Handles the async work. Derived classes can override the
 * following virtual methods (listed in the order in which they're called):
 *
 * - DoExecute (abstract, worker pool thread): main work
 * - HandleOKCallback (main thread): call JS callback on success
 * - HandleErrorCallback (main thread): call JS callback on error
 * - DoFinally (main thread): do cleanup regardless of success
 */
struct BaseWorker {
  // Note: storing env is discouraged as we'd end up using it in unsafe places.
  BaseWorker (napi_env env,
              Database* database,
              napi_value callback,
              const char* resourceName)
    : database_(database) {
    NAPI_STATUS_THROWS_VOID(napi_create_reference(env, callback, 1, &callbackRef_));
    napi_value asyncResourceName;
    NAPI_STATUS_THROWS_VOID(napi_create_string_utf8(env, resourceName,
                                               NAPI_AUTO_LENGTH,
                                               &asyncResourceName));
    NAPI_STATUS_THROWS_VOID(napi_create_async_work(env, callback,
                                              asyncResourceName,
                                              BaseWorker::Execute,
                                              BaseWorker::Complete,
                                              this, &asyncWork_));
  }

  virtual ~BaseWorker () {}

  static void Execute (napi_env env, void* data) {
    auto self = reinterpret_cast<BaseWorker*>(data);

    // Don't pass env to DoExecute() because use of Node-API
    // methods should generally be avoided in async work.
    self->DoExecute();
  }

  void SetStatus (const leveldb::Status& status) {
    status_ = status;
  }

  virtual void DoExecute () = 0;

  static void Complete (napi_env env, napi_status status, void* data) {
    auto self = reinterpret_cast<BaseWorker*>(data);

    self->DoComplete(env);
    self->DoFinally(env);
  }

  void DoComplete (napi_env env) {
    napi_value callback;
    napi_get_reference_value(env, callbackRef_, &callback);

    if (status_.ok()) {
      HandleOKCallback(env, callback);
    } else {
      HandleErrorCallback(env, callback);
    }
  }

  virtual void HandleOKCallback (napi_env env, napi_value callback) {
    napi_value argv;
    napi_get_null(env, &argv);
    CallFunction(env, callback, 1, &argv);
  }

  virtual void HandleErrorCallback (napi_env env, napi_value callback) {
    auto argv = CreateError(env, status_.ToString());
    CallFunction(env, callback, 1, &argv);
  }

  virtual void DoFinally (napi_env env) {
    napi_delete_reference(env, callbackRef_);
    napi_delete_async_work(env, asyncWork_);

    delete this;
  }

  void Queue (napi_env env) {
    napi_queue_async_work(env, asyncWork_);
  }

  Database* database_;

private:
  napi_ref callbackRef_;
  napi_async_work asyncWork_;
  leveldb::Status status_;
};

/**
 * Owns the LevelDB storage, cache, filter policy and iterators.
 */
struct Database {
  Database ()
    : pendingCloseWorker_(nullptr),
      ref_(nullptr),
      priorityWork_(0) {}

  leveldb::Status Open (const leveldb::Options& options,
                        const bool readOnly,
                        const char* location) {
    if (readOnly) {
      leveldb::DB* db = nullptr;
      const auto status = rocksdb::DB::OpenForReadOnly(options, location, &db);
      db_.reset(db);
      return status;
    } else {
      leveldb::DB* db = nullptr;
      const auto status = leveldb::DB::Open(options, location, &db);
      db_.reset(db);
      return status;
    }
  }

  void CloseDatabase () {
    db_.reset();
  }

  leveldb::Status Put (const leveldb::WriteOptions& options,
                       const std::string& key,
                       const std::string& value) {
    return db_->Put(options, key, value);
  }

  leveldb::Status Get (const leveldb::ReadOptions& options,
                       const std::string& key,
                       std::string& value) {
    return db_->Get(options, key, &value);
  }

  leveldb::Status Del (const leveldb::WriteOptions& options,
                       const std::string& key) {
    return db_->Delete(options, key);
  }

  leveldb::Status WriteBatch (const leveldb::WriteOptions& options,
                              leveldb::WriteBatch* batch) {
    return db_->Write(options, batch);
  }

  void GetProperty (const std::string& property, std::string& value) {
    db_->GetProperty(property, &value);
  }

  const leveldb::Snapshot* NewSnapshot () {
    return db_->GetSnapshot();
  }

  leveldb::Iterator* NewIterator (const leveldb::ReadOptions& options) {
    return db_->NewIterator(options);
  }

  void ReleaseSnapshot (const leveldb::Snapshot* snapshot) {
    return db_->ReleaseSnapshot(snapshot);
  }

  void AttachIterator (napi_env env, Iterator* iterator) {
    iterators_.insert(iterator);
    IncrementPriorityWork(env);
  }

  void DetachIterator (napi_env env, Iterator* iterator) {
    iterators_.erase(iterator);
    DecrementPriorityWork(env);
  }

  void IncrementPriorityWork (napi_env env) {
    napi_reference_ref(env, ref_, &priorityWork_);
  }

  void DecrementPriorityWork (napi_env env) {
    napi_reference_unref(env, ref_, &priorityWork_);

    if (priorityWork_ == 0 && pendingCloseWorker_) {
      pendingCloseWorker_->Queue(env);
      pendingCloseWorker_ = nullptr;
    }
  }

  bool HasPriorityWork () const {
    return priorityWork_ > 0;
  }

  std::unique_ptr<leveldb::DB> db_;
  BaseWorker* pendingCloseWorker_;
  std::set<Iterator*> iterators_;
  napi_ref ref_;

private:
  uint32_t priorityWork_;
};

/**
 * Base worker class for doing async work that defers closing the database.
 */
struct PriorityWorker : public BaseWorker {
  PriorityWorker (napi_env env, Database* database, napi_value callback, const char* resourceName)
    : BaseWorker(env, database, callback, resourceName) {
      database_->IncrementPriorityWork(env);
  }

  virtual ~PriorityWorker () {}

  void DoFinally (napi_env env) override {
    database_->DecrementPriorityWork(env);
    BaseWorker::DoFinally(env);
  }
};

struct BaseIterator {
  BaseIterator(Database* database,
               const bool reverse,
               const std::optional<std::string>& lt,
               const std::optional<std::string>& lte,
               const std::optional<std::string>& gt,
               const std::optional<std::string>& gte,
               const int limit,
               const bool fillCache)
    : database_(database),
      snapshot_(database->NewSnapshot()),
      dbIterator_(database->NewIterator([&]{
        leveldb::ReadOptions options;
        options.fill_cache = fillCache;
        options.verify_checksums = false;
        options.snapshot = snapshot_;
        return options;
      }())),
      didSeek_(false),
      reverse_(reverse),
      lt_(lt),
      lte_(lte),
      gt_(gt),
      gte_(gte),
      limit_(limit),
      count_(0) {
  }

  virtual ~BaseIterator () {
    assert(!dbIterator_);
  }

  bool DidSeek () const {
    return didSeek_;
  }

  /**
   * Seek to the first relevant key based on range options.
   */
  void SeekToRange () {
    didSeek_ = true;

    if (!reverse_ && gte_) {
      dbIterator_->Seek(*gte_);
    } else if (!reverse_ && gt_) {
      dbIterator_->Seek(*gt_);

      if (dbIterator_->Valid() && dbIterator_->key().compare(*gt_) == 0) {
        dbIterator_->Next();
      }
    } else if (reverse_ && lte_) {
      dbIterator_->Seek(*lte_);

      if (!dbIterator_->Valid()) {
        dbIterator_->SeekToLast();
      } else if (dbIterator_->key().compare(*lte_) > 0) {
        dbIterator_->Prev();
      }
    } else if (reverse_ && lt_) {
      dbIterator_->Seek(*lt_);

      if (!dbIterator_->Valid()) {
        dbIterator_->SeekToLast();
      } else if (dbIterator_->key().compare(*lt_) >= 0) {
        dbIterator_->Prev();
      }
    } else if (reverse_) {
      dbIterator_->SeekToLast();
    } else {
      dbIterator_->SeekToFirst();
    }
  }

  /**
   * Seek manually (during iteration).
   */
  void Seek (const std::string& target) {
    didSeek_ = true;

    if (OutOfRange(target)) {
      return SeekToEnd();
    }

    dbIterator_->Seek(target);

    if (dbIterator_->Valid()) {
      const auto cmp = dbIterator_->key().compare(target);
      if (reverse_ ? cmp > 0 : cmp < 0) {
        Next();
      }
    } else {
      SeekToFirst();
      if (dbIterator_->Valid()) {
        const auto cmp = dbIterator_->key().compare(target);
        if (reverse_ ? cmp > 0 : cmp < 0) {
          SeekToEnd();
        }
      }
    }
  }

  void Close () {
    if (dbIterator_) {
      delete dbIterator_;
      dbIterator_ = nullptr;
      database_->ReleaseSnapshot(snapshot_);
    }
  }

  bool Valid () const {
    return dbIterator_->Valid() && !OutOfRange(dbIterator_->key());
  }

  bool Increment () {
    return limit_ < 0 || ++count_ <= limit_;
  }

  void Next () {
    if (reverse_) dbIterator_->Prev();
    else dbIterator_->Next();
  }

  void SeekToFirst () {
    if (reverse_) dbIterator_->SeekToLast();
    else dbIterator_->SeekToFirst();
  }

  void SeekToLast () {
    if (reverse_) dbIterator_->SeekToFirst();
    else dbIterator_->SeekToLast();
  }

  void SeekToEnd () {
    SeekToLast();
    Next();
  }

  leveldb::Slice CurrentKey () const {
    return dbIterator_->key();
  }

  leveldb::Slice CurrentValue () const {
    return dbIterator_->value();
  }

  leveldb::Status Status () const {
    return dbIterator_->status();
  }

  bool OutOfRange (const leveldb::Slice& target) const {
    return ((lt_  && target.compare(*lt_) >= 0) ||
            (lte_ && target.compare(*lte_) > 0) ||
            (gt_  && target.compare(*gt_) <= 0) ||
            (gte_ && target.compare(*gte_) < 0));
  }

  Database* database_;

private:
  const leveldb::Snapshot* snapshot_;
  leveldb::Iterator* dbIterator_;
  bool didSeek_;
  const bool reverse_;
  const std::optional<std::string> lt_;
  const std::optional<std::string> lte_;
  const std::optional<std::string> gt_;
  const std::optional<std::string> gte_;
  const int limit_;
  int count_;
};

struct Iterator final : public BaseIterator {
  Iterator (Database* database,
            const bool reverse,
            const bool keys,
            const bool values,
            const int limit,
            const std::optional<std::string>& lt,
            const std::optional<std::string>& lte,
            const std::optional<std::string>& gt,
            const std::optional<std::string>& gte,
            const bool fillCache,
            const bool keyAsBuffer,
            const bool valueAsBuffer,
            const uint32_t highWaterMark)
    : BaseIterator(database, reverse, lt, lte, gt, gte, limit, fillCache),
      keys_(keys),
      values_(values),
      keyAsBuffer_(keyAsBuffer),
      valueAsBuffer_(valueAsBuffer),
      highWaterMark_(highWaterMark),
      landed_(false),
      nexting_(false),
      isClosing_(false),
      closeWorker_(nullptr),
      ref_(nullptr) {
  }

  void Attach (napi_env env, napi_value context) {
    napi_create_reference(env, context, 1, &ref_);
    database_->AttachIterator(env, this);
  }

  void Detach (napi_env env) {
    database_->DetachIterator(env, this);
    if (ref_) napi_delete_reference(env, ref_);
  }

  bool ReadMany (uint32_t size) {
    cache_.clear();
    size_t bytesRead = 0;

    while (true) {
      if (landed_) Next();
      if (!Valid() || !Increment()) break;

      if (keys_) {
        const auto& slice = CurrentKey();
        cache_.emplace_back(slice.data(), slice.size());
        bytesRead += slice.size();
      } else {
        cache_.emplace_back("");
      }

      if (values_) {
        const auto& slice = CurrentValue();
        cache_.emplace_back(slice.data(), slice.size());
        bytesRead += slice.size();
      } else {
        cache_.emplace_back("");
      }

      if (!landed_) {
        landed_ = true;
        return true;
      }

      if (bytesRead > highWaterMark_ || cache_.size() >= size * 2) {
        return true;
      }
    }

    return false;
  }

  const bool keys_;
  const bool values_;
  const bool keyAsBuffer_;
  const bool valueAsBuffer_;
  const uint32_t highWaterMark_;
  bool landed_;
  bool nexting_;
  bool isClosing_;
  BaseWorker* closeWorker_;
  std::vector<std::string> cache_;

private:
  napi_ref ref_;
};

/**
 * Hook for when the environment exits. This hook will be called after
 * already-scheduled napi_async_work items have finished, which gives us
 * the guarantee that no db operations will be in-flight at this time.
 */
static void env_cleanup_hook (void* arg) {
  Database* database = (Database*)arg;

  // Do everything that db_close() does but synchronously. We're expecting that GC
  // did not (yet) collect the database because that would be a user mistake (not
  // closing their db) made during the lifetime of the environment. That's different
  // from an environment being torn down (like the main process or a worker thread)
  // where it's our responsibility to clean up. Note also, the following code must
  // be a safe noop if called before db_open() or after db_close().
  if (database && database->db_) {
    // TODO: does not do `napi_delete_reference(env, iterator->ref_)`. Problem?
    for (auto it = database->iterators_.begin(); it != database->iterators_.end(); ++it) {
      (*it)->Close();
    }

    // Having closed the iterators (and released snapshots) we can safely close.
    database->CloseDatabase();
  }
}

static void FinalizeDatabase (napi_env env, void* data, void* hint) {
  if (data) {
    Database* database = (Database*)data;
    napi_remove_env_cleanup_hook(env, env_cleanup_hook, database);
    if (database->ref_) napi_delete_reference(env, database->ref_);
    delete database;
  }
}

NAPI_METHOD(db_init) {
  Database* database = new Database();
  napi_add_env_cleanup_hook(env, env_cleanup_hook, database);

  napi_value result;
  NAPI_STATUS_THROWS(napi_create_external(env, database,
                                          FinalizeDatabase,
                                          nullptr, &result));

  // Reference counter to prevent GC of database while priority workers are active
  NAPI_STATUS_THROWS(napi_create_reference(env, result, 0, &database->ref_));

  return result;
}

/**
 * Worker class for opening a database.
 * TODO: shouldn't this be a PriorityWorker?
 */
struct OpenWorker final : public BaseWorker {
  OpenWorker (napi_env env,
              Database* database,
              napi_value callback,
              const std::string& location,
              const bool createIfMissing,
              const bool errorIfExists,
              const bool compression,
              const uint32_t writeBufferSize,
              const uint32_t blockSize,
              const uint32_t maxOpenFiles,
              const uint32_t blockRestartInterval,
              const uint32_t maxFileSize,
              const uint32_t cacheSize,
              const std::string& infoLogLevel,
              const bool readOnly)
    : BaseWorker(env, database, callback, "leveldown.db.open"),
      readOnly_(readOnly),
      location_(location) {
    options_.create_if_missing = createIfMissing;
    options_.error_if_exists = errorIfExists;
    options_.compression = compression
      ? leveldb::kSnappyCompression
      : leveldb::kNoCompression;
    options_.write_buffer_size = writeBufferSize;
    options_.max_open_files = maxOpenFiles;
    options_.max_log_file_size = maxFileSize;
    options_.paranoid_checks = false;

    if (infoLogLevel.size() > 0) {
      rocksdb::InfoLogLevel lvl = {};

      if (infoLogLevel == "debug") lvl = rocksdb::InfoLogLevel::DEBUG_LEVEL;
      else if (infoLogLevel == "info") lvl = rocksdb::InfoLogLevel::INFO_LEVEL;
      else if (infoLogLevel == "warn") lvl = rocksdb::InfoLogLevel::WARN_LEVEL;
      else if (infoLogLevel == "error") lvl = rocksdb::InfoLogLevel::ERROR_LEVEL;
      else if (infoLogLevel == "fatal") lvl = rocksdb::InfoLogLevel::FATAL_LEVEL;
      else if (infoLogLevel == "header") lvl = rocksdb::InfoLogLevel::HEADER_LEVEL;
      else napi_throw_error(env, nullptr, "invalid log level");

      options_.info_log_level = lvl;
    } else {
      // In some places RocksDB checks this option to see if it should prepare
      // debug information (ahead of logging), so set it to the highest level.
      options_.info_log_level = rocksdb::InfoLogLevel::HEADER_LEVEL;
      options_.info_log.reset(new NullLogger());
    }

    rocksdb::BlockBasedTableOptions tableOptions;

    if (cacheSize) {
      tableOptions.block_cache = rocksdb::NewLRUCache(cacheSize);
    } else {
      tableOptions.no_block_cache = true;
    }

    tableOptions.block_size = blockSize;
    tableOptions.block_restart_interval = blockRestartInterval;
    tableOptions.filter_policy.reset(rocksdb::NewBloomFilterPolicy(10));

    options_.table_factory.reset(
      rocksdb::NewBlockBasedTableFactory(tableOptions)
    );
  }

  void DoExecute () override {
    SetStatus(database_->Open(options_, readOnly_, location_.c_str()));
  }

  leveldb::Options options_;
  const bool readOnly_;
  const std::string location_;
};

NAPI_METHOD(db_open) {
  NAPI_ARGV(4);
  NAPI_DB_CONTEXT();

  const auto location = ToString(env, argv[1]);
  const auto options = argv[2];
  const auto createIfMissing = BooleanProperty(env, options, "createIfMissing", true);
  const auto errorIfExists = BooleanProperty(env, options, "errorIfExists", false);
  const auto compression = BooleanProperty(env, options, "compression", true);
  const auto readOnly = BooleanProperty(env, options, "readOnly", false);

  const auto infoLogLevel = StringProperty(env, options, "infoLogLevel");

  const auto cacheSize = Uint32Property(env, options, "cacheSize", 8 << 20);
  const auto writeBufferSize = Uint32Property(env, options , "writeBufferSize" , 4 << 20);
  const auto blockSize = Uint32Property(env, options, "blockSize", 4096);
  const auto maxOpenFiles = Uint32Property(env, options, "maxOpenFiles", 1000);
  const auto blockRestartInterval = Uint32Property(env, options,
                                                 "blockRestartInterval", 16);
  const auto maxFileSize = Uint32Property(env, options, "maxFileSize", 2 << 20);

  const auto callback = argv[3];

  auto worker = new OpenWorker(env, database, callback, location,
                               createIfMissing, errorIfExists,
                               compression, writeBufferSize, blockSize,
                               maxOpenFiles, blockRestartInterval,
                               maxFileSize, cacheSize,
                               infoLogLevel, readOnly);
  worker->Queue(env);

  return 0;
}

struct CloseWorker final : public BaseWorker {
  CloseWorker (napi_env env,
               Database* database,
               napi_value callback)
    : BaseWorker(env, database, callback, "leveldown.db.close") {}

  void DoExecute () override {
    database_->CloseDatabase();
  }
};

napi_value noop_callback (napi_env env, napi_callback_info info) {
  return 0;
}

NAPI_METHOD(db_close) {
  NAPI_ARGV(2);
  NAPI_DB_CONTEXT();

  const auto callback = argv[1];

  napi_value noop;
  napi_create_function(env, nullptr, 0, noop_callback, nullptr, &noop);

  for (auto it = database->iterators_.begin(); it != database->iterators_.end(); ++it) {
    iterator_do_close(env, *it, noop);
  }
  
  auto worker = new CloseWorker(env, database, callback);

  if (!database->HasPriorityWork()) {
    worker->Queue(env);
  } else {
    database->pendingCloseWorker_ = worker;
  }

  return 0;
}

struct GetManyWorker final : public PriorityWorker {
  GetManyWorker (napi_env env,
                 Database* database,
                 const std::vector<std::string>& keys,
                 napi_value callback,
                 const bool valueAsBuffer,
                 const bool fillCache)
    : PriorityWorker(env, database, callback, "leveldown.get.many"),
      keys_(keys), valueAsBuffer_(valueAsBuffer), fillCache_(fillCache),
      snapshot_(database->NewSnapshot()) {
  }

  ~GetManyWorker () {
    if (snapshot_) {
      database_->ReleaseSnapshot(snapshot_);
      snapshot_ = nullptr;
    }
  }

  void DoExecute () override {
    cache_.reserve(keys_.size());

    leveldb::ReadOptions options;
    options.snapshot = snapshot_;
    options.fill_cache = fillCache_;
    
    for (const auto& key: keys_) {
      std::string value;
      const auto status = database_->Get(options, key, value);

      if (status.ok()) {
        cache_.push_back(std::move(value));
      } else if (status.IsNotFound()) {
        cache_.push_back({});
      } else {
        SetStatus(status);
        break;
      }
    }

    database_->ReleaseSnapshot(snapshot_);
    snapshot_ = nullptr;
  }

  void HandleOKCallback (napi_env env, napi_value callback) override {
    const auto size = cache_.size();

    napi_value array;
    napi_create_array_with_length(env, size, &array);

    for (size_t idx = 0; idx < size; idx++) {
      napi_value element;
      Convert(env, cache_[idx], valueAsBuffer_, element);
      napi_set_element(env, array, static_cast<uint32_t>(idx), element);
    }

    napi_value argv[2];
    napi_get_null(env, &argv[0]);
    argv[1] = array;
    CallFunction(env, callback, 2, argv);
  }

private:
  const std::vector<std::string> keys_;
  const bool valueAsBuffer_;
  std::vector<std::optional<std::string>> cache_;
  const bool fillCache_;
  const leveldb::Snapshot* snapshot_;
};

NAPI_METHOD(db_get_many) {
  NAPI_ARGV(4);
  NAPI_DB_CONTEXT();

  const auto keys = KeyArray(env, argv[1]);
  const auto options = argv[2];
  const bool asBuffer = BooleanProperty(env, options, "asBuffer", true);
  const bool fillCache = BooleanProperty(env, options, "fillCache", true);
  const auto callback = argv[3];

  auto worker = new GetManyWorker(env, database, keys, callback, asBuffer, fillCache);
  worker->Queue(env);

  return 0;
}

static void FinalizeIterator (napi_env env, void* data, void* hint) {
  if (data) {
    delete reinterpret_cast<Iterator*>(data);
  }
}

NAPI_METHOD(iterator_init) {
  NAPI_ARGV(2);
  NAPI_DB_CONTEXT();

  const auto options = argv[1];
  const auto reverse = BooleanProperty(env, options, "reverse", false);
  const auto keys = BooleanProperty(env, options, "keys", true);
  const auto values = BooleanProperty(env, options, "values", true);
  const auto fillCache = BooleanProperty(env, options, "fillCache", false);
  const auto keyAsBuffer = BooleanProperty(env, options, "keyAsBuffer", true);
  const auto valueAsBuffer = BooleanProperty(env, options, "valueAsBuffer", true);
  const auto limit = Int32Property(env, options, "limit", -1);
  const auto highWaterMark = Uint32Property(env, options, "highWaterMark", 16 * 1024);

  const auto lt = RangeOption(env, options, "lt");
  const auto lte = RangeOption(env, options, "lte");
  const auto gt = RangeOption(env, options, "gt");
  const auto gte = RangeOption(env, options, "gte");

  auto iterator = new Iterator(database, reverse, keys,
                               values, limit, lt, lte, gt, gte, fillCache,
                               keyAsBuffer, valueAsBuffer, highWaterMark);
  napi_value result;

  NAPI_STATUS_THROWS(napi_create_external(env, iterator,
                                          FinalizeIterator,
                                          nullptr, &result));

  // Prevent GC of JS object before the iterator is closed (explicitly or on
  // db close) and keep track of non-closed iterators to end them on db close.
  iterator->Attach(env, result);

  return result;
}

NAPI_METHOD(iterator_seek) {
  NAPI_ARGV(2);
  NAPI_ITERATOR_CONTEXT();

  if (iterator->isClosing_) {
    napi_throw_error(env, nullptr, "iterator has closed");
  }

  const auto target = ToString(env, argv[1]);
  iterator->landed_ = false;
  iterator->Seek(target);

  return 0;
}

struct CloseIteratorWorker final : public BaseWorker {
  CloseIteratorWorker (napi_env env,
                       Iterator* iterator,
                       napi_value callback)
    : BaseWorker(env, iterator->database_, callback, "leveldown.iterator.end"),
      iterator_(iterator) {}

  void DoExecute () override {
    iterator_->Close();
  }

  void DoFinally (napi_env env) override {
    iterator_->Detach(env);
    BaseWorker::DoFinally(env);
  }

private:
  Iterator* iterator_;
};

/**
 * Called by NAPI_METHOD(iterator_) and also when closing
 * open iterators during NAPI_METHOD(db_close).
 */
static void iterator_do_close (napi_env env, Iterator* iterator, napi_value cb) {
  if (!iterator->isClosing_) {
    auto worker = new CloseIteratorWorker(env, iterator, cb);
    iterator->isClosing_ = true;

    if (iterator->nexting_) {
      iterator->closeWorker_ = worker;
    } else {
      worker->Queue(env);
    }
  }
}

NAPI_METHOD(iterator_close) {
  NAPI_ARGV(2);
  NAPI_ITERATOR_CONTEXT();

  iterator_do_close(env, iterator, argv[1]);

  return 0;
}

struct NextWorker final : public BaseWorker {
  NextWorker (napi_env env,
              Iterator* iterator,
              uint32_t size,
              napi_value callback)
    : BaseWorker(env, iterator->database_, callback,
                 "leveldown.iterator.next"),
      iterator_(iterator), size_(size), ok_() {}

  void DoExecute () override {
    if (!iterator_->DidSeek()) {
      iterator_->SeekToRange();
    }

    // Limit the size of the cache to prevent starving the event loop
    // in JS-land while we're recursively calling process.nextTick().
    ok_ = iterator_->ReadMany(size_);

    if (!ok_) {
      SetStatus(iterator_->Status());
    }
  }

  void HandleOKCallback (napi_env env, napi_value callback) override {
    const auto size = iterator_->cache_.size();
    napi_value result;
    napi_create_array_with_length(env, size, &result);

    for (size_t idx = 0; idx < iterator_->cache_.size(); idx += 2) {
      napi_value key;
      napi_value val;

      Convert(env, iterator_->cache_[idx + 0], iterator_->keyAsBuffer_, key);
      Convert(env, iterator_->cache_[idx + 1], iterator_->valueAsBuffer_, val);

      napi_set_element(env, result, static_cast<int>(size - idx - 1), key);
      napi_set_element(env, result, static_cast<int>(size - idx - 2), val);
    }

    iterator_->cache_.clear();

    napi_value argv[3];
    napi_get_null(env, &argv[0]);
    argv[1] = result;
    napi_get_boolean(env, !ok_, &argv[2]);
    CallFunction(env, callback, 3, argv);
  }

  void DoFinally (napi_env env) override {
    // clean up & handle the next/end state
    iterator_->nexting_ = false;

    if (iterator_->closeWorker_) {
      iterator_->closeWorker_->Queue(env);
      iterator_->closeWorker_ = nullptr;
    }

    BaseWorker::DoFinally(env);
  }

private:
  Iterator* iterator_;
  uint32_t size_;
  bool ok_;
};

NAPI_METHOD(iterator_nextv) {
  NAPI_ARGV(3);
  NAPI_ITERATOR_CONTEXT();

  uint32_t size;
  NAPI_STATUS_THROWS(napi_get_value_uint32(env, argv[1], &size));
  if (size == 0) size = 1;

  const auto callback = argv[2];

  if (iterator->isClosing_) {
    auto argv = CreateError(env, "iterator has closed");
    CallFunction(env, callback, 1, &argv);

    return 0;
  }

  auto worker = new NextWorker(env, iterator, size, callback);
  iterator->nexting_ = true;
  worker->Queue(env);

  return 0;
}

static void FinalizeBatch (napi_env env, void* data, void* hint) {
  if (data) {
    delete reinterpret_cast<leveldb::WriteBatch*>(data);
  }
}

NAPI_METHOD(batch_init) {
  NAPI_ARGV(1);
  NAPI_DB_CONTEXT();

  auto batch = new leveldb::WriteBatch();

  napi_value result;
  NAPI_STATUS_THROWS(napi_create_external(env, batch,
                                          FinalizeBatch,
                                          nullptr, &result));
  return result;
}

NAPI_METHOD(batch_put) {
  NAPI_ARGV(3);
  NAPI_BATCH_CONTEXT();

  const auto key = ToString(env, argv[1]);
  const auto value = ToString(env, argv[2]);

  batch->Put(key, value);

  return 0;
}

NAPI_METHOD(batch_del) {
  NAPI_ARGV(2);
  NAPI_BATCH_CONTEXT();

  const auto key = ToString(env, argv[1]);

  batch->Delete(key);

  return 0;
}

NAPI_METHOD(batch_clear) {
  NAPI_ARGV(1);
  NAPI_BATCH_CONTEXT();

  batch->Clear();

  return 0;
}

struct BatchWriteWorker final : public PriorityWorker {
  BatchWriteWorker (napi_env env,
                    Database* database,
                    napi_value batch,
                    napi_value callback,
                    const bool sync)
    : PriorityWorker(env, database, callback, "leveldown.batch.write"),
      sync_(sync) {

    NAPI_STATUS_THROWS_VOID(napi_get_value_external(env, batch, reinterpret_cast<void**>(&batch_)));

    // Prevent GC of batch object before we execute
    NAPI_STATUS_THROWS_VOID(napi_create_reference(env, batch, 1, &batchRef_));
  }

  void DoExecute () override {
    leveldb::WriteOptions options;
    options.sync = sync_;
    SetStatus(database_->WriteBatch(options, batch_));
  }

  void DoFinally (napi_env env) override {
    napi_delete_reference(env, batchRef_);
    PriorityWorker::DoFinally(env);
  }

private:
  leveldb::WriteBatch* batch_;
  const bool sync_;
  napi_ref batchRef_;
};

NAPI_METHOD(batch_write) {
  NAPI_ARGV(4);
  NAPI_DB_CONTEXT();

  const auto batch = argv[1];
  const auto options = argv[2];
  const auto sync = BooleanProperty(env, options, "sync", false);
  const auto callback = argv[3];

  auto worker = new BatchWriteWorker(env, database, batch, callback, sync);
  worker->Queue(env);

  return 0;
}

NAPI_INIT() {
  NAPI_EXPORT_FUNCTION(db_init);
  NAPI_EXPORT_FUNCTION(db_open);
  NAPI_EXPORT_FUNCTION(db_close);
  NAPI_EXPORT_FUNCTION(db_get_many);

  NAPI_EXPORT_FUNCTION(iterator_init);
  NAPI_EXPORT_FUNCTION(iterator_seek);
  NAPI_EXPORT_FUNCTION(iterator_close);
  NAPI_EXPORT_FUNCTION(iterator_nextv);

  NAPI_EXPORT_FUNCTION(batch_init);
  NAPI_EXPORT_FUNCTION(batch_put);
  NAPI_EXPORT_FUNCTION(batch_del);
  NAPI_EXPORT_FUNCTION(batch_clear);
  NAPI_EXPORT_FUNCTION(batch_write);
}
