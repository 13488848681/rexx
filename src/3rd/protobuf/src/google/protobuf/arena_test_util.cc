
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/arena_test_util.h>


#define EXPECT_EQ GOOGLE_CHECK_EQ

namespace google {
namespace protobuf {
namespace internal {

NoHeapChecker::~NoHeapChecker() {
  capture_alloc.Unhook();
  EXPECT_EQ(0, capture_alloc.alloc_count());
  EXPECT_EQ(0, capture_alloc.free_count());
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google
