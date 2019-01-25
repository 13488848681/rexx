
#ifndef GOOGLE_PROTOBUF_ATOMICOPS_INTERNALS_PPC_GCC_H_
#define GOOGLE_PROTOBUF_ATOMICOPS_INTERNALS_PPC_GCC_H_

#define ATOMICOPS_COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")

namespace google {
namespace protobuf {
namespace internal {

inline Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32 *ptr,
                                         Atomic32 old_value,
                                         Atomic32 new_value) {
  Atomic32 prev;

  __asm__ __volatile__(
      "0:                                  \n\t"
      "lwarx %[prev],0,%[ptr]              \n\t"
      "cmpw 0,%[prev],%[old_value]         \n\t"
      "bne- 1f                             \n\t"
      "stwcx. %[new_value],0,%[ptr]        \n\t"
      "bne- 0b                             \n\t"
      "1:                                  \n\t"
      : [prev] "=&r"(prev), "+m"(*ptr)
      : [ptr] "r"(ptr), [old_value] "r"(old_value), [new_value] "r"(new_value)
      : "cc", "memory");

  return prev;
}

inline Atomic32 NoBarrier_AtomicExchange(volatile Atomic32 *ptr,
                                         Atomic32 new_value) {
  Atomic32 old;

  __asm__ __volatile__(
      "0:                                  \n\t"
      "lwarx %[old],0,%[ptr]               \n\t"
      "stwcx. %[new_value],0,%[ptr]        \n\t"
      "bne- 0b                             \n\t"
      : [old] "=&r"(old), "+m"(*ptr)
      : [ptr] "r"(ptr), [new_value] "r"(new_value)
      : "cc", "memory");

  return old;
}

inline Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32 *ptr,
                                          Atomic32 increment) {
  Atomic32 temp;

  __asm__ __volatile__(
      "0:                                  \n\t"
      "lwarx %[temp],0,%[ptr]              \n\t"
      "add %[temp],%[increment],%[temp]    \n\t"
      "stwcx. %[temp],0,%[ptr]             \n\t"
      "bne- 0b                             \n\t"
      : [temp] "=&r"(temp)
      : [increment] "r"(increment), [ptr] "r"(ptr)
      : "cc", "memory");

  return temp;
}

inline Atomic32 Barrier_AtomicIncrement(volatile Atomic32 *ptr,
                                        Atomic32 increment) {
  MemoryBarrier();
  Atomic32 res = NoBarrier_AtomicIncrement(ptr, increment);
  MemoryBarrier();
  return res;
}

inline Atomic32 Acquire_CompareAndSwap(volatile Atomic32 *ptr,
                                       Atomic32 old_value, Atomic32 new_value) {
  Atomic32 res = NoBarrier_CompareAndSwap(ptr, old_value, new_value);
  MemoryBarrier();
  return res;
}

inline Atomic32 Release_CompareAndSwap(volatile Atomic32 *ptr,
                                       Atomic32 old_value, Atomic32 new_value) {
  MemoryBarrier();
  Atomic32 res = NoBarrier_CompareAndSwap(ptr, old_value, new_value);
  return res;
}

inline void NoBarrier_Store(volatile Atomic32 *ptr, Atomic32 value) {
  *ptr = value;
}

inline void MemoryBarrier() { __asm__ __volatile__("sync" : : : "memory"); }

inline void Acquire_Store(volatile Atomic32 *ptr, Atomic32 value) {
  *ptr = value;
  MemoryBarrier();
}

inline void Release_Store(volatile Atomic32 *ptr, Atomic32 value) {
  MemoryBarrier();
  *ptr = value;
}

inline Atomic32 NoBarrier_Load(volatile const Atomic32 *ptr) { return *ptr; }

inline Atomic32 Acquire_Load(volatile const Atomic32 *ptr) {
  Atomic32 value = *ptr;
  MemoryBarrier();
  return value;
}

inline Atomic32 Release_Load(volatile const Atomic32 *ptr) {
  MemoryBarrier();
  return *ptr;
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#undef ATOMICOPS_COMPILER_BARRIER

#endif  // GOOGLE_PROTOBUF_ATOMICOPS_INTERNALS_PPC_GCC_H_
