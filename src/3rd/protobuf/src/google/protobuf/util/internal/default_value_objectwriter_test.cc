
#include <google/protobuf/util/internal/default_value_objectwriter.h>
#include <google/protobuf/util/internal/expecting_objectwriter.h>
#include <google/protobuf/util/internal/testdata/default_value_test.pb.h>
#include <google/protobuf/util/internal/type_info_test_helper.h>
#include <google/protobuf/util/internal/constants.h>
#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {
namespace testing {

using google::protobuf::testing::DefaultValueTest;

// Base class for setting up required state for running default values tests on
// different descriptors.
class BaseDefaultValueObjectWriterTest
    : public ::testing::TestWithParam<testing::TypeInfoSource> {
 protected:
  explicit BaseDefaultValueObjectWriterTest(const Descriptor* descriptor)
      : helper_(GetParam()), mock_(), expects_(&mock_) {
    helper_.ResetTypeInfo(descriptor);
    testing_.reset(helper_.NewDefaultValueWriter(
        string(kTypeServiceBaseUrl) + "/" + descriptor->full_name(), &mock_));
  }

  virtual ~BaseDefaultValueObjectWriterTest() {}

  TypeInfoTestHelper helper_;
  MockObjectWriter mock_;
  ExpectingObjectWriter expects_;
  google::protobuf::scoped_ptr<DefaultValueObjectWriter> testing_;
};

// Tests to cover some basic DefaultValueObjectWriter use cases. More tests are
// in the marshalling_test.cc and translator_integration_test.cc.
class DefaultValueObjectWriterTest : public BaseDefaultValueObjectWriterTest {
 protected:
  DefaultValueObjectWriterTest()
      : BaseDefaultValueObjectWriterTest(DefaultValueTest::descriptor()) {}
  virtual ~DefaultValueObjectWriterTest() {}
};

INSTANTIATE_TEST_CASE_P(DifferentTypeInfoSourceTest,
                        DefaultValueObjectWriterTest,
                        ::testing::Values(
                            testing::USE_TYPE_RESOLVER));

TEST_P(DefaultValueObjectWriterTest, Empty) {
  // Set expectation
  expects_.StartObject("")
      ->RenderDouble("doubleValue", 0.0)
      ->StartList("repeatedDouble")
      ->EndList()
      ->RenderFloat("floatValue", 0.0)
      ->RenderInt64("int64Value", 0)
      ->RenderUint64("uint64Value", 0)
      ->RenderInt32("int32Value", 0)
      ->RenderUint32("uint32Value", 0)
      ->RenderBool("boolValue", false)
      ->RenderString("stringValue", "")
      ->RenderBytes("bytesValue", "")
      ->RenderString("enumValue", "ENUM_FIRST")
      ->EndObject();

  // Actual testing
  testing_->StartObject("")->EndObject();
}

TEST_P(DefaultValueObjectWriterTest, NonDefaultDouble) {
  // Set expectation
  expects_.StartObject("")
      ->RenderDouble("doubleValue", 1.0)
      ->StartList("repeatedDouble")
      ->EndList()
      ->RenderFloat("floatValue", 0.0)
      ->RenderInt64("int64Value", 0)
      ->RenderUint64("uint64Value", 0)
      ->RenderInt32("int32Value", 0)
      ->RenderUint32("uint32Value", 0)
      ->RenderBool("boolValue", false)
      ->RenderString("stringValue", "")
      ->RenderString("enumValue", "ENUM_FIRST")
      ->EndObject();

  // Actual testing
  testing_->StartObject("")->RenderDouble("doubleValue", 1.0)->EndObject();
}

TEST_P(DefaultValueObjectWriterTest, ShouldRetainUnknownField) {
  // Set expectation
  expects_.StartObject("")
      ->RenderDouble("doubleValue", 1.0)
      ->StartList("repeatedDouble")
      ->EndList()
      ->RenderFloat("floatValue", 0.0)
      ->RenderInt64("int64Value", 0)
      ->RenderUint64("uint64Value", 0)
      ->RenderInt32("int32Value", 0)
      ->RenderUint32("uint32Value", 0)
      ->RenderBool("boolValue", false)
      ->RenderString("stringValue", "")
      ->RenderString("unknown", "abc")
      ->StartObject("unknownObject")
      ->RenderString("unknown", "def")
      ->EndObject()
      ->RenderString("enumValue", "ENUM_FIRST")
      ->EndObject();

  // Actual testing
  testing_->StartObject("")
      ->RenderDouble("doubleValue", 1.0)
      ->RenderString("unknown", "abc")
      ->StartObject("unknownObject")
      ->RenderString("unknown", "def")
      ->EndObject()
      ->EndObject();
}


class DefaultValueObjectWriterSuppressListTest
    : public BaseDefaultValueObjectWriterTest {
 protected:
  DefaultValueObjectWriterSuppressListTest()
      : BaseDefaultValueObjectWriterTest(DefaultValueTest::descriptor()) {
    testing_->set_suppress_empty_list(true);
  }
  ~DefaultValueObjectWriterSuppressListTest() {}
};

INSTANTIATE_TEST_CASE_P(DifferentTypeInfoSourceTest,
                        DefaultValueObjectWriterSuppressListTest,
                        ::testing::Values(
                            testing::USE_TYPE_RESOLVER));

TEST_P(DefaultValueObjectWriterSuppressListTest, Empty) {
  // Set expectation. Emtpy lists should be suppressed.
  expects_.StartObject("")
      ->RenderDouble("doubleValue", 0.0)
      ->RenderFloat("floatValue", 0.0)
      ->RenderInt64("int64Value", 0)
      ->RenderUint64("uint64Value", 0)
      ->RenderInt32("int32Value", 0)
      ->RenderUint32("uint32Value", 0)
      ->RenderBool("boolValue", false)
      ->RenderString("stringValue", "")
      ->RenderBytes("bytesValue", "")
      ->RenderString("enumValue", "ENUM_FIRST")
      ->EndObject();

  // Actual testing
  testing_->StartObject("")->EndObject();
}
}  // namespace testing
}  // namespace converter
}  // namespace util
}  // namespace protobuf
}  // namespace google
