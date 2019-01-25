
#ifndef ROCKSDB_LITE

#include "rocksdb/utilities/convenience.h"

#include "db/db_impl.h"

namespace rocksdb {

void CancelAllBackgroundWork(DB* db) {
  (dynamic_cast<DBImpl*>(db))->CancelAllBackgroundWork();
}
}  // namespace rocksdb

#endif  // ROCKSDB_LITE
