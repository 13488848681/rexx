
#include <algorithm>

#include <google/protobuf/repeated_field.h>
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {

namespace internal {

void** RepeatedPtrFieldBase::InternalExtend(int extend_amount) {
  int new_size = current_size_ + extend_amount;
  if (total_size_ >= new_size) {
    // N.B.: rep_ is non-NULL because extend_amount is always > 0, hence
    // total_size must be non-zero since it is lower-bounded by new_size.
    return &rep_->elements[current_size_];
  }
  Rep* old_rep = rep_;
  Arena* arena = GetArenaNoVirtual();
  new_size = std::max(kMinRepeatedFieldAllocationSize,
                      std::max(total_size_ * 2, new_size));
  GOOGLE_CHECK_LE(new_size,
           (std::numeric_limits<size_t>::max() - kRepHeaderSize) /
           sizeof(old_rep->elements[0]))
      << "Requested size is too large to fit into size_t.";
  if (arena == NULL) {
    rep_ = reinterpret_cast<Rep*>(
        new char[kRepHeaderSize + sizeof(old_rep->elements[0]) * new_size]);
  } else {
    rep_ = reinterpret_cast<Rep*>(
        ::google::protobuf::Arena::CreateArray<char>(arena,
            kRepHeaderSize + sizeof(old_rep->elements[0]) * new_size));
  }
  total_size_ = new_size;
  if (old_rep && old_rep->allocated_size > 0) {
    memcpy(rep_->elements, old_rep->elements,
           old_rep->allocated_size * sizeof(rep_->elements[0]));
    rep_->allocated_size = old_rep->allocated_size;
  } else {
    rep_->allocated_size = 0;
  }
  if (arena == NULL) {
    delete [] reinterpret_cast<char*>(old_rep);
  }
  return &rep_->elements[current_size_];
}

void RepeatedPtrFieldBase::Reserve(int new_size) {
  if (new_size > current_size_) {
    InternalExtend(new_size - current_size_);
  }
}

void RepeatedPtrFieldBase::CloseGap(int start, int num) {
  if (rep_ == NULL) return;
  // Close up a gap of "num" elements starting at offset "start".
  for (int i = start + num; i < rep_->allocated_size; ++i)
    rep_->elements[i - num] = rep_->elements[i];
  current_size_ -= num;
  rep_->allocated_size -= num;
}

}  // namespace internal


}  // namespace protobuf
}  // namespace google
