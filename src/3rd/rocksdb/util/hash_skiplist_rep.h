
#ifndef ROCKSDB_LITE
#pragma once
#include "rocksdb/slice_transform.h"
#include "rocksdb/memtablerep.h"

namespace rocksdb {

class HashSkipListRepFactory : public MemTableRepFactory {
 public:
  explicit HashSkipListRepFactory(
    size_t bucket_count,
    int32_t skiplist_height,
    int32_t skiplist_branching_factor)
      : bucket_count_(bucket_count),
        skiplist_height_(skiplist_height),
        skiplist_branching_factor_(skiplist_branching_factor) { }

  virtual ~HashSkipListRepFactory() {}

  virtual MemTableRep* CreateMemTableRep(
      const MemTableRep::KeyComparator& compare, MemTableAllocator* allocator,
      const SliceTransform* transform, Logger* logger) override;

  virtual const char* Name() const override {
    return "HashSkipListRepFactory";
  }

 private:
  const size_t bucket_count_;
  const int32_t skiplist_height_;
  const int32_t skiplist_branching_factor_;
};

}
#endif  // ROCKSDB_LITE
