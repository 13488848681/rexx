
#include <google/protobuf/generated_message_util.h>

#include <limits>


namespace google {
namespace protobuf {
namespace internal {

double Infinity() {
  return std::numeric_limits<double>::infinity();
}
double NaN() {
  return std::numeric_limits<double>::quiet_NaN();
}

const ::std::string* empty_string_;
GOOGLE_PROTOBUF_DECLARE_ONCE(empty_string_once_init_);

void DeleteEmptyString() {
  delete empty_string_;
}

void InitEmptyString() {
  empty_string_ = new string;
  OnShutdown(&DeleteEmptyString);
}

int StringSpaceUsedExcludingSelf(const string& str) {
  const void* start = &str;
  const void* end = &str + 1;
  if (start <= str.data() && str.data() < end) {
    // The string's data is stored inside the string object itself.
    return 0;
  } else {
    return str.capacity();
  }
}



void MergeFromFail(const char* file, int line) {
  GOOGLE_CHECK(false) << file << ":" << line;
  // Open-source GOOGLE_CHECK(false) is not NORETURN.
  exit(1);
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google
