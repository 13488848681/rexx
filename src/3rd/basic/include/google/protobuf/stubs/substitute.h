

#include <string>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/strutil.h>

#ifndef GOOGLE_PROTOBUF_STUBS_SUBSTITUTE_H_
#define GOOGLE_PROTOBUF_STUBS_SUBSTITUTE_H_

namespace google {
namespace protobuf {
namespace strings {

namespace internal {  // Implementation details.

class SubstituteArg {
 public:
  inline SubstituteArg(const char* value)
    : text_(value), size_(strlen(text_)) {}
  inline SubstituteArg(const string& value)
    : text_(value.data()), size_(value.size()) {}

  // Indicates that no argument was given.
  inline explicit SubstituteArg()
    : text_(NULL), size_(-1) {}

  // Primitives
  // We don't overload for signed and unsigned char because if people are
  // explicitly declaring their chars as signed or unsigned then they are
  // probably actually using them as 8-bit integers and would probably
  // prefer an integer representation.  But, we don't really know.  So, we
  // make the caller decide what to do.
  inline SubstituteArg(char value)
    : text_(scratch_), size_(1) { scratch_[0] = value; }
  inline SubstituteArg(short value)
    : text_(FastInt32ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(unsigned short value)
    : text_(FastUInt32ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(int value)
    : text_(FastInt32ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(unsigned int value)
    : text_(FastUInt32ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(long value)
    : text_(FastLongToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(unsigned long value)
    : text_(FastULongToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(long long value)
    : text_(FastInt64ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(unsigned long long value)
    : text_(FastUInt64ToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(float value)
    : text_(FloatToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(double value)
    : text_(DoubleToBuffer(value, scratch_)), size_(strlen(text_)) {}
  inline SubstituteArg(bool value)
    : text_(value ? "true" : "false"), size_(strlen(text_)) {}

  inline const char* data() const { return text_; }
  inline int size() const { return size_; }

 private:
  const char* text_;
  int size_;
  char scratch_[kFastToBufferSize];
};

}  // namespace internal

LIBPROTOBUF_EXPORT string Substitute(
  const char* format,
  const internal::SubstituteArg& arg0 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg1 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg2 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg3 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg4 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg5 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg6 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg7 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg8 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg9 = internal::SubstituteArg());

LIBPROTOBUF_EXPORT void SubstituteAndAppend(
  string* output, const char* format,
  const internal::SubstituteArg& arg0 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg1 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg2 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg3 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg4 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg5 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg6 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg7 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg8 = internal::SubstituteArg(),
  const internal::SubstituteArg& arg9 = internal::SubstituteArg());

}  // namespace strings
}  // namespace protobuf
}  // namespace google

#endif // GOOGLE_PROTOBUF_STUBS_SUBSTITUTE_H_
