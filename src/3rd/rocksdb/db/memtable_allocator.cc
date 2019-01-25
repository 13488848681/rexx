
#include <assert.h>

#include "db/memtable_allocator.h"
#include "db/writebuffer.h"
#include "util/arena.h"

namespace rocksdb {

MemTableAllocator::MemTableAllocator(Arena* arena, WriteBuffer* write_buffer)
    : arena_(arena), write_buffer_(write_buffer), bytes_allocated_(0) {
}

MemTableAllocator::~MemTableAllocator() {
  DoneAllocating();
}

char* MemTableAllocator::Allocate(size_t bytes) {
  assert(write_buffer_ != nullptr);
  bytes_allocated_ += bytes;
  write_buffer_->ReserveMem(bytes);
  return arena_->Allocate(bytes);
}

char* MemTableAllocator::AllocateAligned(size_t bytes, size_t huge_page_size,
                                         Logger* logger) {
  assert(write_buffer_ != nullptr);
  bytes_allocated_ += bytes;
  write_buffer_->ReserveMem(bytes);
  return arena_->AllocateAligned(bytes, huge_page_size, logger);
}

void MemTableAllocator::DoneAllocating() {
  if (write_buffer_ != nullptr) {
    write_buffer_->FreeMem(bytes_allocated_);
    write_buffer_ = nullptr;
  }
}

size_t MemTableAllocator::BlockSize() const {
  return arena_->BlockSize();
}

}  // namespace rocksdb
