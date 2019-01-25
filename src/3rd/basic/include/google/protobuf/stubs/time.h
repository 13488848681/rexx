
#ifndef GOOGLE_PROTOBUF_STUBS_TIME_H_
#define GOOGLE_PROTOBUF_STUBS_TIME_H_

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
namespace internal {

struct DateTime {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

// Converts a timestamp (seconds elapsed since 1970-01-01T00:00:00, could be
// negative to represent time before 1970-01-01) to DateTime. Returns false
// if the timestamp is not in the range between 0001-01-01T00:00:00 and
// 9999-12-31T23:59:59.
bool LIBPROTOBUF_EXPORT SecondsToDateTime(int64 seconds, DateTime* time);
// Converts DateTime to a timestamp (seconds since 1970-01-01T00:00:00).
// Returns false if the DateTime is not valid or is not in the valid range.
bool LIBPROTOBUF_EXPORT DateTimeToSeconds(const DateTime& time, int64* seconds);

void LIBPROTOBUF_EXPORT GetCurrentTime(int64* seconds, int32* nanos);

// Formats a time string in RFC3339 fromat.
//
// For example, "2015-05-20T13:29:35.120Z". For nanos, 0, 3, 6 or 9 fractional
// digits will be used depending on how many are required to represent the exact
// value.
//
// Note that "nanos" must in the range of [0, 999999999].
string LIBPROTOBUF_EXPORT FormatTime(int64 seconds, int32 nanos);
// Parses a time string. This method accepts RFC3339 date/time string with UTC
// offset. For example, "2015-05-20T13:29:35.120-08:00".
bool LIBPROTOBUF_EXPORT ParseTime(const string& value, int64* seconds, int32* nanos);

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_STUBS_TIME_H_
