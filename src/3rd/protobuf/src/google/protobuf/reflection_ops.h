
#ifndef GOOGLE_PROTOBUF_REFLECTION_OPS_H__
#define GOOGLE_PROTOBUF_REFLECTION_OPS_H__

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/message.h>

namespace google {
namespace protobuf {
namespace internal {

// Basic operations that can be performed using reflection.
// These can be used as a cheap way to implement the corresponding
// methods of the Message interface, though they are likely to be
// slower than implementations tailored for the specific message type.
//
// This class should stay limited to operations needed to implement
// the Message interface.
//
// This class is really a namespace that contains only static methods.
class LIBPROTOBUF_EXPORT ReflectionOps {
 public:
  static void Copy(const Message& from, Message* to);
  static void Merge(const Message& from, Message* to);
  static void Clear(Message* message);
  static bool IsInitialized(const Message& message);
  static void DiscardUnknownFields(Message* message);

  // Finds all unset required fields in the message and adds their full
  // paths (e.g. "foo.bar[5].baz") to *names.  "prefix" will be attached to
  // the front of each name.
  static void FindInitializationErrors(const Message& message,
                                       const string& prefix,
                                       vector<string>* errors);

 private:
  // All methods are static.  No need to construct.
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ReflectionOps);
};

}  // namespace internal
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_REFLECTION_OPS_H__
