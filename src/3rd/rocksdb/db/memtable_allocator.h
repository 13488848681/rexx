
#pragma once
#include "util/allocator.h"

namespace rocksdb {

class Arena;
class Logger;
class WriteBuffer;

class MemTableAllocator : public Allocator {
 public:
  explicit MemTableAllocator(Arena* arena, WriteBuffer* write_buffer);
  ~MemTableAllocator();

  // Allocator interface
  char* Allocate(size_t bytes) override;
  char* AllocateAligned(size_t bytes, size_t huge_page_size = 0,
                        Logger* logger = nullptr) override;
  size_t BlockSize() const override;

  // Call when we're finished allocating memory so we can free it from
  // the write buffer's limit.
  void DoneAllocating();

 private:
  Arena* arena_;
  WriteBuffer* write_buffer_;
  size_t bytes_allocated_;

  // No copying allowed
  MemTableAllocator(const MemTableAllocator&);
  void operator=(const MemTableAllocator&);
};

}  // namespace rocksdb
