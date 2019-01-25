
#ifndef GRPC_IMPL_CODEGEN_SLICE_H
#define GRPC_IMPL_CODEGEN_SLICE_H

#include <stddef.h>
#include <stdint.h>

#include <grpc/impl/codegen/exec_ctx_fwd.h>
#include <grpc/impl/codegen/gpr_slice.h>

typedef struct grpc_slice grpc_slice;


typedef struct grpc_slice_refcount_vtable {
  void (*ref)(void *);
  void (*unref)(grpc_exec_ctx *exec_ctx, void *);
  int (*eq)(grpc_slice a, grpc_slice b);
  uint32_t (*hash)(grpc_slice slice);
} grpc_slice_refcount_vtable;

/* Reference count container for grpc_slice. Contains function pointers to
   increment and decrement reference counts. Implementations should cleanup
   when the reference count drops to zero.
   Typically client code should not touch this, and use grpc_slice_malloc,
   grpc_slice_new, or grpc_slice_new_with_len instead. */
typedef struct grpc_slice_refcount {
  const grpc_slice_refcount_vtable *vtable;
  /* If a subset of this slice is taken, use this pointer for the refcount.
     Typically points back to the refcount itself, however iterning
     implementations can use this to avoid a verification step on each hash
     or equality check */
  struct grpc_slice_refcount *sub_refcount;
} grpc_slice_refcount;

#define GRPC_SLICE_INLINED_SIZE (sizeof(size_t) + sizeof(uint8_t *) - 1)

/* A grpc_slice s, if initialized, represents the byte range
   s.bytes[0..s.length-1].

   It can have an associated ref count which has a destruction routine to be run
   when the ref count reaches zero (see grpc_slice_new() and grp_slice_unref()).
   Multiple grpc_slice values may share a ref count.

   If the slice does not have a refcount, it represents an inlined small piece
   of data that is copied by value. */
struct grpc_slice {
  struct grpc_slice_refcount *refcount;
  union {
    struct {
      uint8_t *bytes;
      size_t length;
    } refcounted;
    struct {
      uint8_t length;
      uint8_t bytes[GRPC_SLICE_INLINED_SIZE];
    } inlined;
  } data;
};

#define GRPC_SLICE_BUFFER_INLINE_ELEMENTS 8

/* Represents an expandable array of slices, to be interpreted as a
   single item. */
typedef struct {
  /* This is for internal use only. External users (i.e any code outside grpc
   * core) MUST NOT use this field */
  grpc_slice *base_slices;

  /* slices in the array (Points to the first valid grpc_slice in the array) */
  grpc_slice *slices;
  /* the number of slices in the array */
  size_t count;
  /* the number of slices allocated in the array. External users (i.e any code
   * outside grpc core) MUST NOT use this field */
  size_t capacity;
  /* the combined length of all slices in the array */
  size_t length;
  /* inlined elements to avoid allocations */
  grpc_slice inlined[GRPC_SLICE_BUFFER_INLINE_ELEMENTS];
} grpc_slice_buffer;

#define GRPC_SLICE_START_PTR(slice)                 \
  ((slice).refcount ? (slice).data.refcounted.bytes \
                    : (slice).data.inlined.bytes)
#define GRPC_SLICE_LENGTH(slice)                     \
  ((slice).refcount ? (slice).data.refcounted.length \
                    : (slice).data.inlined.length)
#define GRPC_SLICE_SET_LENGTH(slice, newlen)                              \
  ((slice).refcount ? ((slice).data.refcounted.length = (size_t)(newlen)) \
                    : ((slice).data.inlined.length = (uint8_t)(newlen)))
#define GRPC_SLICE_END_PTR(slice) \
  GRPC_SLICE_START_PTR(slice) + GRPC_SLICE_LENGTH(slice)
#define GRPC_SLICE_IS_EMPTY(slice) (GRPC_SLICE_LENGTH(slice) == 0)

#ifdef GRPC_ALLOW_GPR_SLICE_FUNCTIONS

/* Duplicate GPR_* definitions */
#define GPR_SLICE_START_PTR(slice)                  \
  ((slice).refcount ? (slice).data.refcounted.bytes \
                    : (slice).data.inlined.bytes)
#define GPR_SLICE_LENGTH(slice)                      \
  ((slice).refcount ? (slice).data.refcounted.length \
                    : (slice).data.inlined.length)
#define GPR_SLICE_SET_LENGTH(slice, newlen)                               \
  ((slice).refcount ? ((slice).data.refcounted.length = (size_t)(newlen)) \
                    : ((slice).data.inlined.length = (uint8_t)(newlen)))
#define GPR_SLICE_END_PTR(slice) \
  GRPC_SLICE_START_PTR(slice) + GRPC_SLICE_LENGTH(slice)
#define GPR_SLICE_IS_EMPTY(slice) (GRPC_SLICE_LENGTH(slice) == 0)

#endif /* GRPC_ALLOW_GPR_SLICE_FUNCTIONS */

#endif /* GRPC_IMPL_CODEGEN_SLICE_H */
