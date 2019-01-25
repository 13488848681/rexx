
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_SOURCE_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_SOURCE_H__

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/stringpiece.h>
#include <google/protobuf/stubs/status.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

class ObjectWriter;

// An ObjectSource is anything that can write to an ObjectWriter.
// Implementation of this interface typically provide constructors or
// factory methods to create an instance based on some source data, for
// example, a character stream, or protobuf.
//
// Derived classes could be thread-unsafe.
class LIBPROTOBUF_EXPORT ObjectSource {
 public:
  virtual ~ObjectSource() {}

  // Writes to the ObjectWriter
  virtual util::Status WriteTo(ObjectWriter* ow) const {
    return NamedWriteTo("", ow);
  }

  // Writes to the ObjectWriter with a custom name for the message.
  // This is useful when you chain ObjectSource together by embedding one
  // within another.
  virtual util::Status NamedWriteTo(StringPiece name,
                                      ObjectWriter* ow) const = 0;

 protected:
  ObjectSource() {}

 private:
  // Do not add any data members to this class.
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ObjectSource);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_SOURCE_H__
