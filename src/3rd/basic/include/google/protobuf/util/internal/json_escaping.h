
#ifndef NET_PROTO2_UTIL_CONVERTER_STRINGS_JSON_ESCAPING_H_
#define NET_PROTO2_UTIL_CONVERTER_STRINGS_JSON_ESCAPING_H_

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/bytestream.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

class JsonEscaping {
 public:
  // The minimum value of a unicode high-surrogate code unit in the utf-16
  // encoding. A high-surrogate is also known as a leading-surrogate.
  // See http://www.unicode.org/glossary/#high_surrogate_code_unit
  static const uint16 kMinHighSurrogate = 0xd800;

  // The maximum value of a unicide high-surrogate code unit in the utf-16
  // encoding. A high-surrogate is also known as a leading-surrogate.
  // See http://www.unicode.org/glossary/#high_surrogate_code_unit
  static const uint16 kMaxHighSurrogate = 0xdbff;

  // The minimum value of a unicode low-surrogate code unit in the utf-16
  // encoding. A low-surrogate is also known as a trailing-surrogate.
  // See http://www.unicode.org/glossary/#low_surrogate_code_unit
  static const uint16 kMinLowSurrogate = 0xdc00;

  // The maximum value of a unicode low-surrogate code unit in the utf-16
  // encoding. A low-surrogate is also known as a trailing surrogate.
  // See http://www.unicode.org/glossary/#low_surrogate_code_unit
  static const uint16 kMaxLowSurrogate = 0xdfff;

  // The minimum value of a unicode supplementary code point.
  // See http://www.unicode.org/glossary/#supplementary_code_point
  static const uint32 kMinSupplementaryCodePoint = 0x010000;

  // The minimum value of a unicode code point.
  // See http://www.unicode.org/glossary/#code_point
  static const uint32 kMinCodePoint = 0x000000;

  // The maximum value of a unicode code point.
  // See http://www.unicode.org/glossary/#code_point
  static const uint32 kMaxCodePoint = 0x10ffff;

  JsonEscaping() {}
  virtual ~JsonEscaping() {}

  // Escape the given ByteSource to the given ByteSink.
  static void Escape(strings::ByteSource* input, strings::ByteSink* output);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(JsonEscaping);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

#endif  // NET_PROTO2_UTIL_CONVERTER_STRINGS_JSON_ESCAPING_H_
}  // namespace google
