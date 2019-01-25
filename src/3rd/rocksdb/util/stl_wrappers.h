
#pragma once

#include "util/murmurhash.h"
#include "util/coding.h"

#include "rocksdb/memtablerep.h"
#include "rocksdb/slice.h"

namespace rocksdb {
namespace stl_wrappers {
  class Base {
   protected:
    const MemTableRep::KeyComparator& compare_;
    explicit Base(const MemTableRep::KeyComparator& compare)
      : compare_(compare) { }
  };

  struct Compare : private Base {
    explicit Compare(const MemTableRep::KeyComparator& compare)
      : Base(compare) { }
    inline bool operator()(const char* a, const char* b) const {
      return compare_(a, b) < 0;
    }
  };

}
}
