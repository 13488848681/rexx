
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_FIELD_MASK_UTILITY_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_FIELD_MASK_UTILITY_H__

#include <functional>
#include <stack>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/stringpiece.h>
#include <google/protobuf/stubs/status.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

typedef string (*ConverterCallback)(StringPiece);
typedef ResultCallback1<util::Status, StringPiece>* PathSinkCallback;

// Applies a 'converter' to each segment of a FieldMask path and returns the
// result. Quoted strings in the 'path' are copied to the output as-is without
// converting their content. Escaping is supported within quoted strings.
// For example, "ab\"_c" will be returned as "ab\"_c" without any changes.
string ConvertFieldMaskPath(const StringPiece path,
                            ConverterCallback converter);

// Decodes a compact list of FieldMasks. For example, "a.b,a.c.d,a.c.e" will be
// decoded into a list of field paths - "a.b", "a.c.d", "a.c.e". And the results
// will be sent to 'path_sink', i.e. 'path_sink' will be called once per
// resulting path.
// Note that we also support Apiary style FieldMask form. The above example in
// the Apiary style will look like "a.b,a.c(d,e)".
util::Status DecodeCompactFieldMaskPaths(StringPiece paths,
                                           PathSinkCallback path_sink);

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_FIELD_MASK_UTILITY_H__
