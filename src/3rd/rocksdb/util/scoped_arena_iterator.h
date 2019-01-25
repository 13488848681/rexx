
#pragma once

#include "rocksdb/iterator.h"

namespace rocksdb {
class ScopedArenaIterator {
 public:
  explicit ScopedArenaIterator(Iterator* iter = nullptr) : iter_(iter) {}

  Iterator* operator->() { return iter_; }

  void set(Iterator* iter) { iter_ = iter; }

  Iterator* get() { return iter_; }

  ~ScopedArenaIterator() { iter_->~Iterator(); }

 private:
  Iterator* iter_;
};
}  // namespace rocksdb
