
#include <string>

#pragma once
#include "rocksdb/status.h"
#include "rocksdb/types.h"
#include "rocksdb/env.h"

namespace rocksdb {

extern Status CopyFile(Env* env, const std::string& source,
                       const std::string& destination, uint64_t size = 0);

}  // namespace rocksdb
