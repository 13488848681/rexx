
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_H__

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/type.pb.h>
#include <google/protobuf/util/type_resolver.h>
#include <google/protobuf/stubs/stringpiece.h>
#include <google/protobuf/stubs/status.h>
#include <google/protobuf/stubs/statusor.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {
// Internal helper class for type resolving. Note that this class is not
// thread-safe and should only be accessed in one thread.
class LIBPROTOBUF_EXPORT TypeInfo {
 public:
  TypeInfo() {}
  virtual ~TypeInfo() {}

  // Resolves a type url into a Type. If the type url is invalid, returns
  // INVALID_ARGUMENT error status. If the type url is valid but the
  // corresponding type cannot be found, returns a NOT_FOUND error status.
  //
  // This TypeInfo class retains the ownership of the returned pointer.
  virtual util::StatusOr<const google::protobuf::Type*> ResolveTypeUrl(
      StringPiece type_url) const = 0;

  // Resolves a type url into a Type. Like ResolveTypeUrl() but returns
  // NULL if the type url is invalid or the type cannot be found.
  //
  // This TypeInfo class retains the ownership of the returned pointer.
  virtual const google::protobuf::Type* GetTypeByTypeUrl(
      StringPiece type_url) const = 0;

  // Resolves a type url for an enum. Returns NULL if the type url is
  // invalid or the type cannot be found.
  //
  // This TypeInfo class retains the ownership of the returned pointer.
  virtual const google::protobuf::Enum* GetEnumByTypeUrl(
      StringPiece type_url) const = 0;

  // Looks up a field in the specified type given a CamelCase name.
  virtual const google::protobuf::Field* FindField(
      const google::protobuf::Type* type,
      StringPiece camel_case_name) const = 0;

  // Creates a TypeInfo object that looks up type information from a
  // TypeResolver. Caller takes ownership of the returned pointer.
  static TypeInfo* NewTypeInfo(TypeResolver* type_resolver);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypeInfo);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_H__
