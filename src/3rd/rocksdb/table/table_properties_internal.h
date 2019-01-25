
#pragma once

#include "rocksdb/status.h"
#include "rocksdb/iterator.h"

namespace rocksdb {

// Seek to the properties block.
// If it successfully seeks to the properties block, "is_found" will be
// set to true.
Status SeekToPropertiesBlock(Iterator* meta_iter, bool* is_found);

}  // namespace rocksdb
