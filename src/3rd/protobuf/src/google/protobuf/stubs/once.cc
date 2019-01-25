
#include <google/protobuf/stubs/once.h>

#ifndef GOOGLE_PROTOBUF_NO_THREAD_SAFETY

#ifdef _WIN32
#include <windows.h>
#else
#include <sched.h>
#endif

#include <google/protobuf/stubs/atomicops.h>

namespace google {
namespace protobuf {

namespace {

void SchedYield() {
#ifdef _WIN32
  Sleep(0);
#else  // POSIX
  sched_yield();
#endif
}

}  // namespace

void GoogleOnceInitImpl(ProtobufOnceType* once, Closure* closure) {
  internal::AtomicWord state = internal::Acquire_Load(once);
  // Fast path. The provided closure was already executed.
  if (state == ONCE_STATE_DONE) {
    return;
  }
  // The closure execution did not complete yet. The once object can be in one
  // of the two following states:
  //   - UNINITIALIZED: We are the first thread calling this function.
  //   - EXECUTING_CLOSURE: Another thread is already executing the closure.
  //
  // First, try to change the state from UNINITIALIZED to EXECUTING_CLOSURE
  // atomically.
  state = internal::Acquire_CompareAndSwap(
      once, ONCE_STATE_UNINITIALIZED, ONCE_STATE_EXECUTING_CLOSURE);
  if (state == ONCE_STATE_UNINITIALIZED) {
    // We are the first thread to call this function, so we have to call the
    // closure.
    closure->Run();
    internal::Release_Store(once, ONCE_STATE_DONE);
  } else {
    // Another thread has already started executing the closure. We need to
    // wait until it completes the initialization.
    while (state == ONCE_STATE_EXECUTING_CLOSURE) {
      // Note that futex() could be used here on Linux as an improvement.
      SchedYield();
      state = internal::Acquire_Load(once);
    }
  }
}

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_NO_THREAD_SAFETY
