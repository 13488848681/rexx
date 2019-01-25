
#ifndef GOOGLE_PROTOBUF_STUBS_MUTEX_H_
#define GOOGLE_PROTOBUF_STUBS_MUTEX_H_

#ifdef GOOGLE_PROTOBUF_NO_THREADLOCAL
#include <pthread.h>
#endif

#include <google/protobuf/stubs/macros.h>

// ===================================================================
// emulates google3/base/mutex.h
namespace google {
namespace protobuf {
namespace internal {

// A Mutex is a non-reentrant (aka non-recursive) mutex.  At most one thread T
// may hold a mutex at a given time.  If T attempts to Lock() the same Mutex
// while holding it, T will deadlock.
class LIBPROTOBUF_EXPORT Mutex {
 public:
  // Create a Mutex that is not held by anybody.
  Mutex();

  // Destructor
  ~Mutex();

  // Block if necessary until this Mutex is free, then acquire it exclusively.
  void Lock();

  // Release this Mutex.  Caller must hold it exclusively.
  void Unlock();

  // Crash if this Mutex is not held exclusively by this thread.
  // May fail to crash when it should; will never crash when it should not.
  void AssertHeld();

 private:
  struct Internal;
  Internal* mInternal;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(Mutex);
};

// Undefine the macros  to workaround the conflicts with Google internal
// MutexLock implementation.
// TODO(liujisi): Remove the undef once internal macros are removed.
#undef MutexLock
#undef ReaderMutexLock
#undef WriterMutexLock
#undef MutexLockMaybe

// MutexLock(mu) acquires mu when constructed and releases it when destroyed.
class LIBPROTOBUF_EXPORT MutexLock {
 public:
  explicit MutexLock(Mutex *mu) : mu_(mu) { this->mu_->Lock(); }
  ~MutexLock() { this->mu_->Unlock(); }
 private:
  Mutex *const mu_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MutexLock);
};

// TODO(kenton):  Implement these?  Hard to implement portably.
typedef MutexLock ReaderMutexLock;
typedef MutexLock WriterMutexLock;

// MutexLockMaybe is like MutexLock, but is a no-op when mu is NULL.
class LIBPROTOBUF_EXPORT MutexLockMaybe {
 public:
  explicit MutexLockMaybe(Mutex *mu) :
    mu_(mu) { if (this->mu_ != NULL) { this->mu_->Lock(); } }
  ~MutexLockMaybe() { if (this->mu_ != NULL) { this->mu_->Unlock(); } }
 private:
  Mutex *const mu_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MutexLockMaybe);
};

#if defined(GOOGLE_PROTOBUF_NO_THREADLOCAL)
template<typename T>
class ThreadLocalStorage {
 public:
  ThreadLocalStorage() {
    pthread_key_create(&key_, &ThreadLocalStorage::Delete);
  }
  ~ThreadLocalStorage() {
    pthread_key_delete(key_);
  }
  T* Get() {
    T* result = static_cast<T*>(pthread_getspecific(key_));
    if (result == NULL) {
      result = new T();
      pthread_setspecific(key_, result);
    }
    return result;
  }
 private:
  static void Delete(void* value) {
    delete static_cast<T*>(value);
  }
  pthread_key_t key_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ThreadLocalStorage);
};
#endif

}  // namespace internal

// We made these internal so that they would show up as such in the docs,
// but we don't want to stick "internal::" in front of them everywhere.
using internal::Mutex;
using internal::MutexLock;
using internal::ReaderMutexLock;
using internal::WriterMutexLock;
using internal::MutexLockMaybe;


}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_STUBS_MUTEX_H_
