#include <rocksdb/db.h>

#include "leveldown.h"
#include "leveldown_async.h"

namespace leveldown {

/** DESTROY WORKER **/

DestroyWorker::DestroyWorker (
    Nan::Utf8String* location
  , Nan::Callback *callback
) : AsyncWorker(NULL, callback, "rocksdb:destroy")
  , location(location)
{};

DestroyWorker::~DestroyWorker () {
  delete location;
}

void DestroyWorker::Execute () {
  rocksdb::Options options;
  SetStatus(rocksdb::DestroyDB(**location, options));
}

/** REPAIR WORKER **/

RepairWorker::RepairWorker (
    Nan::Utf8String* location
  , Nan::Callback *callback
) : AsyncWorker(NULL, callback, "rocksdb:repair")
  , location(location)
{};

RepairWorker::~RepairWorker () {
  delete location;
}

void RepairWorker::Execute () {
  rocksdb::Options options;
  SetStatus(rocksdb::RepairDB(**location, options));
}

} // namespace leveldown
