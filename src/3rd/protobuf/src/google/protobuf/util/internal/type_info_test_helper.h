
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_TEST_HELPER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_TEST_HELPER_H__

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <vector>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/util/internal/default_value_objectwriter.h>
#include <google/protobuf/util/internal/type_info.h>
#include <google/protobuf/util/internal/protostream_objectsource.h>
#include <google/protobuf/util/internal/protostream_objectwriter.h>
#include <google/protobuf/util/type_resolver.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {
namespace testing {

enum TypeInfoSource {
  USE_TYPE_RESOLVER,
};

// In the unit-tests we want to test two scenarios: one with type info from
// ServiceTypeInfo, the other with type info from TypeResolver. This class
// wraps the detail of where the type info is from and provides the same
// interface so the same unit-test code can test both scenarios.
class TypeInfoTestHelper {
 public:
  explicit TypeInfoTestHelper(TypeInfoSource type) : type_(type) {}

  // Creates a TypeInfo object for the given set of descriptors.
  void ResetTypeInfo(const vector<const Descriptor*>& descriptors);

  // Convinent overloads.
  void ResetTypeInfo(const Descriptor* descriptor);
  void ResetTypeInfo(const Descriptor* descriptor1,
                     const Descriptor* descriptor2);

  // Returns the TypeInfo created after ResetTypeInfo.
  TypeInfo* GetTypeInfo();

  ProtoStreamObjectSource* NewProtoSource(io::CodedInputStream* coded_input,
                                          const string& type_url);

  ProtoStreamObjectWriter* NewProtoWriter(
      const string& type_url, strings::ByteSink* output,
      ErrorListener* listener, const ProtoStreamObjectWriter::Options& options);

  DefaultValueObjectWriter* NewDefaultValueWriter(const string& type_url,
                                                  ObjectWriter* writer);

 private:
  TypeInfoSource type_;
  google::protobuf::scoped_ptr<TypeInfo> typeinfo_;
  google::protobuf::scoped_ptr<TypeResolver> type_resolver_;
};
}  // namespace testing
}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_TYPE_INFO_TEST_HELPER_H__
