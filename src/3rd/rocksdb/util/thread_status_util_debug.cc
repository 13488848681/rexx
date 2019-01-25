
#include <atomic>

#include "rocksdb/env.h"
#include "util/thread_status_updater.h"
#include "util/thread_status_util.h"

namespace rocksdb {

#ifndef NDEBUG
// the delay for debugging purpose.
static std::atomic<int> states_delay[ThreadStatus::NUM_STATE_TYPES];

void ThreadStatusUtil::TEST_SetStateDelay(
    const ThreadStatus::StateType state, int micro) {
  states_delay[state].store(micro, std::memory_order_relaxed);
}

void ThreadStatusUtil::TEST_StateDelay(const ThreadStatus::StateType state) {
  auto delay = states_delay[state].load(std::memory_order_relaxed);
  if (delay > 0) {
    Env::Default()->SleepForMicroseconds(delay);
  }
}

#endif  // !NDEBUG

}  // namespace rocksdb
