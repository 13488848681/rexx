
#include <sstream>
#include <string>
#include <vector>
#include "util/string_util.h"

namespace rocksdb {

std::vector<std::string> StringSplit(const std::string& arg, char delim) {
  std::vector<std::string> splits;
  std::stringstream ss(arg);
  std::string item;
  while (std::getline(ss, item, delim)) {
    splits.push_back(item);
  }
  return splits;
}

}  // namespace rocksdb
