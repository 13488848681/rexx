
#include <google/protobuf/arenastring.h>

namespace google {
namespace protobuf {
namespace internal {


void ArenaStringPtr::AssignWithDefault(const ::std::string* default_value,
                                       ArenaStringPtr value) {
  const ::std::string* me = *UnsafeRawStringPointer();
  const ::std::string* other = *value.UnsafeRawStringPointer();
  // If the pointers are the same then do nothing.
  if (me != other) {
    SetNoArena(default_value, value.GetNoArena(default_value));
  }
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google
