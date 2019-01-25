
#include <sstream>
#include "rocksdb/env.h"
#include "util/iostats_context_imp.h"

namespace rocksdb {

#ifndef IOS_CROSS_COMPILE
__thread IOStatsContext iostats_context;
#endif  // IOS_CROSS_COMPILE

void IOStatsContext::Reset() {
  thread_pool_id = Env::Priority::TOTAL;
  bytes_read = 0;
  bytes_written = 0;
}

#define OUTPUT(counter) #counter << " = " << counter << ", "

std::string IOStatsContext::ToString() const {
  std::ostringstream ss;
  ss << OUTPUT(thread_pool_id)
     << OUTPUT(bytes_read)
     << OUTPUT(bytes_written);
  return ss.str();
}

}  // namespace rocksdb
