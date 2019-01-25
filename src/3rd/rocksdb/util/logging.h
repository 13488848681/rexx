
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string>
#include "port/port.h"

namespace rocksdb {

class Slice;

// Append a human-readable time in micros.
int AppendHumanMicros(uint64_t micros, char* output, int len,
                      bool fixed_format);

// Append a human-readable size in bytes
int AppendHumanBytes(uint64_t bytes, char* output, int len);

// Append a human-readable printout of "num" to *str
extern void AppendNumberTo(std::string* str, uint64_t num);

// Append a human-readable printout of "value" to *str.
// Escapes any non-printable characters found in "value".
extern void AppendEscapedStringTo(std::string* str, const Slice& value);

// Return a string printout of "num"
extern std::string NumberToString(uint64_t num);

// Return a human-readable version of num.
// for num >= 10.000, prints "xxK"
// for num >= 10.000.000, prints "xxM"
// for num >= 10.000.000.000, prints "xxG"
extern std::string NumberToHumanString(int64_t num);

// Return a human-readable version of "value".
// Escapes any non-printable characters found in "value".
extern std::string EscapeString(const Slice& value);

// Parse a human-readable number from "*in" into *value.  On success,
// advances "*in" past the consumed number and sets "*val" to the
// numeric value.  Otherwise, returns false and leaves *in in an
// unspecified state.
extern bool ConsumeDecimalNumber(Slice* in, uint64_t* val);

}  // namespace rocksdb
