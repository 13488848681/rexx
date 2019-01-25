
#include <google/protobuf/util/internal/type_info_test_helper.h>

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <vector>

#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/util/internal/default_value_objectwriter.h>
#include <google/protobuf/util/internal/type_info.h>
#include <google/protobuf/util/internal/constants.h>
#include <google/protobuf/util/internal/protostream_objectsource.h>
#include <google/protobuf/util/internal/protostream_objectwriter.h>
#include <google/protobuf/util/type_resolver.h>
#include <google/protobuf/util/type_resolver_util.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {
namespace testing {


void TypeInfoTestHelper::ResetTypeInfo(
    const vector<const Descriptor*>& descriptors) {
  switch (type_) {
    case USE_TYPE_RESOLVER: {
      const DescriptorPool* pool = descriptors[0]->file()->pool();
      for (int i = 1; i < descriptors.size(); ++i) {
        GOOGLE_CHECK(pool == descriptors[i]->file()->pool())
            << "Descriptors from different pools are not supported.";
      }
      type_resolver_.reset(
          NewTypeResolverForDescriptorPool(kTypeServiceBaseUrl, pool));
      typeinfo_.reset(TypeInfo::NewTypeInfo(type_resolver_.get()));
      return;
    }
  }
  GOOGLE_LOG(FATAL) << "Can not reach here.";
}

void TypeInfoTestHelper::ResetTypeInfo(const Descriptor* descriptor) {
  vector<const Descriptor*> descriptors;
  descriptors.push_back(descriptor);
  ResetTypeInfo(descriptors);
}

void TypeInfoTestHelper::ResetTypeInfo(const Descriptor* descriptor1,
                                       const Descriptor* descriptor2) {
  vector<const Descriptor*> descriptors;
  descriptors.push_back(descriptor1);
  descriptors.push_back(descriptor2);
  ResetTypeInfo(descriptors);
}

TypeInfo* TypeInfoTestHelper::GetTypeInfo() { return typeinfo_.get(); }

ProtoStreamObjectSource* TypeInfoTestHelper::NewProtoSource(
    io::CodedInputStream* coded_input, const string& type_url) {
  const google::protobuf::Type* type = typeinfo_->GetTypeByTypeUrl(type_url);
  switch (type_) {
    case USE_TYPE_RESOLVER: {
      return new ProtoStreamObjectSource(coded_input, type_resolver_.get(),
                                         *type);
    }
  }
  GOOGLE_LOG(FATAL) << "Can not reach here.";
  return NULL;
}

ProtoStreamObjectWriter* TypeInfoTestHelper::NewProtoWriter(
    const string& type_url, strings::ByteSink* output, ErrorListener* listener,
    const ProtoStreamObjectWriter::Options& options) {
  const google::protobuf::Type* type = typeinfo_->GetTypeByTypeUrl(type_url);
  switch (type_) {
    case USE_TYPE_RESOLVER: {
      return new ProtoStreamObjectWriter(type_resolver_.get(), *type, output,
                                         listener, options);
    }
  }
  GOOGLE_LOG(FATAL) << "Can not reach here.";
  return NULL;
}

DefaultValueObjectWriter* TypeInfoTestHelper::NewDefaultValueWriter(
    const string& type_url, ObjectWriter* writer) {
  const google::protobuf::Type* type = typeinfo_->GetTypeByTypeUrl(type_url);
  switch (type_) {
    case USE_TYPE_RESOLVER: {
      return new DefaultValueObjectWriter(type_resolver_.get(), *type, writer);
    }
  }
  GOOGLE_LOG(FATAL) << "Can not reach here.";
  return NULL;
}

}  // namespace testing
}  // namespace converter
}  // namespace util
}  // namespace protobuf
}  // namespace google
