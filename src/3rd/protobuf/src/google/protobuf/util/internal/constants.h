

#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_CONSTANTS_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_CONSTANTS_H__

#include <google/protobuf/stubs/common.h>

// This file contains constants used by //net/proto2/util/converter.

namespace google {
namespace protobuf {
namespace util {
namespace converter {
// Prefix for type URLs.
const char kTypeServiceBaseUrl[] = "type.googleapis.com";

// Format string for RFC3339 timestamp formatting.
const char kRfc3339TimeFormat[] = "%E4Y-%m-%dT%H:%M:%S";

// Same as above, but the year value is not zero-padded i.e. this accepts
// timestamps like "1-01-0001T23:59:59Z" instead of "0001-01-0001T23:59:59Z".
const char kRfc3339TimeFormatNoPadding[] = "%Y-%m-%dT%H:%M:%S";

// Minimun seconds allowed in a google.protobuf.Timestamp value.
const int64 kTimestampMinSeconds = -62135596800;

// Maximum seconds allowed in a google.protobuf.Timestamp value.
const int64 kTimestampMaxSeconds = 253402300799;

// Minimum seconds allowed in a google.protobuf.Duration value.
const int64 kDurationMinSeconds = -315576000000;

// Maximum seconds allowed in a google.protobuf.Duration value.
const int64 kDurationMaxSeconds = 315576000000;

// Nano seconds in a second.
const int32 kNanosPerSecond = 1000000000;

// Type url representing NULL values in google.protobuf.Struct type.
const char kStructNullValueTypeUrl[] =
    "type.googleapis.com/google.protobuf.NullValue";

// Type string for google.protobuf.Struct
const char kStructType[] = "google.protobuf.Struct";

// Type string for struct.proto's google.protobuf.Value value type.
const char kStructValueType[] = "google.protobuf.Value";

// Type string for struct.proto's google.protobuf.ListValue value type.
const char kStructListValueType[] = "google.protobuf.ListValue";

// Type string for google.protobuf.Timestamp
const char kTimestampType[] = "google.protobuf.Timestamp";

// Type string for google.protobuf.Duration
const char kDurationType[] = "google.protobuf.Duration";

// Type URL for struct value type google.protobuf.Value
const char kStructValueTypeUrl[] = "type.googleapis.com/google.protobuf.Value";

// Type URL for struct value type google.protobuf.Value
const char kStructTypeUrl[] = "type.googleapis.com/google.protobuf.Struct";

// Type string for google.protobuf.Any
const char kAnyType[] = "google.protobuf.Any";

// The type URL of google.protobuf.FieldMask;
const char kFieldMaskTypeUrl[] =
    "type.googleapis.com/google.protobuf.FieldMask";

}  // namespace converter
}  // namespace util
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_CONSTANTS_H__
