
#pragma once

#include <string>

#include "rocksdb/options.h"

namespace rocksdb {
void DumpDBFileSummary(const DBOptions& options, const std::string& dbname);
}  // namespace rocksdb
