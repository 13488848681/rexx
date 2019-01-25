
#include <sstream>
#include <string>
#include <vector>

#pragma once
namespace rocksdb {

extern std::vector<std::string> StringSplit(const std::string& arg, char delim);

template <typename T>
inline std::string ToString(T value) {
#ifndef OS_ANDROID
  return std::to_string(value);
#else
  // Andorid doesn't support all of C++11, std::to_string() being
  // one of the not supported features.
  std::ostringstream os;
  os << value;
  return os.str();
#endif
}

}  // namespace rocksdb
