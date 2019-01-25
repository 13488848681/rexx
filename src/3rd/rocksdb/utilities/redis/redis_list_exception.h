
#ifndef ROCKSDB_LITE
#pragma once
#include <exception>

namespace rocksdb {

class RedisListException: public std::exception {
 public:
  const char* what() const throw() override {
    return "Invalid operation or corrupt data in Redis List.";
  }
};

} // namespace rocksdb
#endif
