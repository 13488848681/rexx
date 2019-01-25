
#ifndef GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_H__
#define GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_H__

#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/status.h>


namespace google {
namespace protobuf {
class Type;
class Enum;
}  // namespace protobuf


namespace protobuf {
class DescriptorPool;
namespace util {

// Abstract interface for a type resovler.
//
// Implementations of this interface must be thread-safe.
class LIBPROTOBUF_EXPORT TypeResolver {
 public:
  TypeResolver() {}
  virtual ~TypeResolver() {}

  // Resolves a type url for a message type.
  virtual util::Status ResolveMessageType(
      const string& type_url, google::protobuf::Type* message_type) = 0;

  // Resolves a type url for an enum type.
  virtual util::Status ResolveEnumType(const string& type_url,
                                         google::protobuf::Enum* enum_type) = 0;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypeResolver);
};

}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_H__
