
#ifndef GRPCXX_SUPPORT_SLICE_H
#define GRPCXX_SUPPORT_SLICE_H

#include <grpc++/support/config.h>
#include <grpc/slice.h>

namespace grpc {

class Slice final {
 public:
  /// Construct an empty slice.
  Slice();
  // Destructor - drops one reference.
  ~Slice();

  enum AddRef { ADD_REF };
  /// Construct a slice from \a slice, adding a reference.
  Slice(grpc_slice slice, AddRef);

  enum StealRef { STEAL_REF };
  /// Construct a slice from \a slice, stealing a reference.
  Slice(grpc_slice slice, StealRef);

  /// Copy constructor, adds a reference.
  Slice(const Slice& other);

  /// Assignment, reference count is unchanged.
  Slice& operator=(Slice other) {
    std::swap(slice_, other.slice_);
    return *this;
  }

  /// Byte size.
  size_t size() const { return GRPC_SLICE_LENGTH(slice_); }

  /// Raw pointer to the beginning (first element) of the slice.
  const uint8_t* begin() const { return GRPC_SLICE_START_PTR(slice_); }

  /// Raw pointer to the end (one byte \em past the last element) of the slice.
  const uint8_t* end() const { return GRPC_SLICE_END_PTR(slice_); }

  /// Raw C slice. Caller needs to call grpc_slice_unref when done.
  grpc_slice c_slice() const { return grpc_slice_ref(slice_); }

 private:
  friend class ByteBuffer;

  grpc_slice slice_;
};

}  // namespace grpc

#endif  // GRPCXX_SUPPORT_SLICE_H
