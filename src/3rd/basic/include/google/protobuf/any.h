
#ifndef GOOGLE_PROTOBUF_ANY_H__
#define GOOGLE_PROTOBUF_ANY_H__

#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/arenastring.h>

namespace google {
namespace protobuf {
namespace internal {

// Helper class used to implement google::protobuf::Any.
class LIBPROTOBUF_EXPORT AnyMetadata {
  typedef ArenaStringPtr UrlType;
  typedef ArenaStringPtr ValueType;
 public:
  // AnyMetadata does not take ownership of "type_url" and "value".
  AnyMetadata(UrlType* type_url, ValueType* value);

  // Packs a message using the default type URL prefix: "type.googleapis.com".
  // The resulted type URL will be "type.googleapis.com/<message_full_name>".
  void PackFrom(const Message& message);
  // Packs a message using the given type URL prefix. The type URL will be
  // constructed by concatenating the message type's full name to the prefix
  // with an optional "/" separator if the prefix doesn't already end up "/".
  // For example, both PackFrom(message, "type.googleapis.com") and
  // PackFrom(message, "type.googleapis.com/") yield the same result type
  // URL: "type.googleapis.com/<message_full_name>".
  void PackFrom(const Message& message, const string& type_url_prefix);

  // Unpacks the payload into the given message. Returns false if the message's
  // type doesn't match the type specified in the type URL (i.e., the full
  // name after the last "/" of the type URL doesn't match the message's actaul
  // full name) or parsing the payload has failed.
  bool UnpackTo(Message* message) const;

  // Checks whether the type specified in the type URL matches the given type.
  // A type is consdiered matching if its full name matches the full name after
  // the last "/" in the type URL.
  template<typename T>
  bool Is() const {
    return InternalIs(T::default_instance().GetDescriptor());
  }

 private:
  bool InternalIs(const Descriptor* message) const;

  UrlType* type_url_;
  ValueType* value_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(AnyMetadata);
};

extern const char kAnyFullTypeName[];          // "google.protobuf.Any".
extern const char kTypeGoogleApisComPrefix[];  // "type.googleapis.com/".
extern const char kTypeGoogleProdComPrefix[];  // "type.googleprod.com/".

// Get the proto type name from Any::type_url value. For example, passing
// "type.googleapis.com/rpc.QueryOrigin" will return "rpc.QueryOrigin" in
// *full_type_name. Returns false if type_url does not start with
// "type.googleapis.com" or "type.googleprod.com".
bool ParseAnyTypeUrl(const string& type_url, string* full_type_name);

// See if message is of type google.protobuf.Any, if so, return the descriptors
// for "type_url" and "value" fields.
bool GetAnyFieldDescriptors(const Message& message,
                            const FieldDescriptor** type_url_field,
                            const FieldDescriptor** value_field);

}  // namespace internal
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_ANY_H__
