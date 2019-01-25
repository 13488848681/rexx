

#ifndef GOOGLE_PROTOBUF_IO_STRTOD_H__
#define GOOGLE_PROTOBUF_IO_STRTOD_H__

namespace google {
namespace protobuf {
namespace io {

// A locale-independent version of the standard strtod(), which always
// uses a dot as the decimal separator.
double NoLocaleStrtod(const char* str, char** endptr);

// Casts a double value to a float value. If the value is outside of the
// representable range of float, it will be converted to positive or negative
// infinity.
float SafeDoubleToFloat(double value);

}  // namespace io
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_IO_STRTOD_H__
