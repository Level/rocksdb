#include <rocksdb/write_batch.h>
#include "batch.h"
#include "batch_async.h"

namespace leveldown {

/** NEXT WORKER **/

BatchWriteWorker::BatchWriteWorker (
    Batch* batch
  , Nan::Callback *callback
) : AsyncWorker(NULL, callback, "rocksdb:batch.write")
  , batch(batch)
{};

BatchWriteWorker::~BatchWriteWorker () {}

void BatchWriteWorker::Execute () {
  SetStatus(batch->Write());
}

} // namespace leveldown
