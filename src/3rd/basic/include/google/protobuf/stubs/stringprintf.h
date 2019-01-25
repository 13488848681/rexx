
#ifndef GOOGLE_PROTOBUF_STUBS_STRINGPRINTF_H
#define GOOGLE_PROTOBUF_STUBS_STRINGPRINTF_H

#include <stdarg.h>
#include <string>
#include <vector>

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {

// Return a C++ string
LIBPROTOBUF_EXPORT extern string StringPrintf(const char* format, ...);

// Store result into a supplied string and return it
LIBPROTOBUF_EXPORT extern const string& SStringPrintf(string* dst, const char* format, ...);

// Append result to a supplied string
LIBPROTOBUF_EXPORT extern void StringAppendF(string* dst, const char* format, ...);

// Lower-level routine that takes a va_list and appends to a specified
// string.  All other routines are just convenience wrappers around it.
LIBPROTOBUF_EXPORT extern void StringAppendV(string* dst, const char* format, va_list ap);

// The max arguments supported by StringPrintfVector
LIBPROTOBUF_EXPORT extern const int kStringPrintfVectorMaxArgs;

// You can use this version when all your arguments are strings, but
// you don't know how many arguments you'll have at compile time.
// StringPrintfVector will LOG(FATAL) if v.size() > kStringPrintfVectorMaxArgs
LIBPROTOBUF_EXPORT extern string StringPrintfVector(const char* format, const vector<string>& v);

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_STUBS_STRINGPRINTF_H
