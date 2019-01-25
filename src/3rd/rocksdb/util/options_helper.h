
#pragma once

#include <string>
#include <stdexcept>
#include "util/mutable_cf_options.h"
#include "rocksdb/status.h"

namespace rocksdb {

Status GetMutableOptionsFromStrings(
    const MutableCFOptions& base_options,
    const std::unordered_map<std::string, std::string>& options_map,
    MutableCFOptions* new_options);

}  // namespace rocksdb
