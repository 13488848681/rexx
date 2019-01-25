
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif

#include <google/protobuf/unittest_drop_unknown_fields.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <gtest/gtest.h>

namespace google {
using unittest_drop_unknown_fields::Foo;
using unittest_drop_unknown_fields::FooWithExtraFields;

namespace protobuf {

TEST(DropUnknownFieldsTest, GeneratedMessage) {
  FooWithExtraFields foo_with_extra_fields;
  foo_with_extra_fields.set_int32_value(1);
  foo_with_extra_fields.set_enum_value(FooWithExtraFields::QUX);
  foo_with_extra_fields.set_extra_int32_value(2);

  Foo foo;
  ASSERT_TRUE(foo.ParseFromString(foo_with_extra_fields.SerializeAsString()));
  EXPECT_EQ(1, foo.int32_value());
  EXPECT_EQ(static_cast<int>(FooWithExtraFields::QUX),
            static_cast<int>(foo.enum_value()));
  // We don't generate unknown field accessors but the UnknownFieldSet is
  // still exposed through reflection API.
  EXPECT_TRUE(foo.GetReflection()->GetUnknownFields(foo).empty());

  ASSERT_TRUE(foo_with_extra_fields.ParseFromString(foo.SerializeAsString()));
  EXPECT_EQ(1, foo_with_extra_fields.int32_value());
  EXPECT_EQ(FooWithExtraFields::QUX, foo_with_extra_fields.enum_value());
  // The "extra_int32_value" field should be lost.
  EXPECT_EQ(0, foo_with_extra_fields.extra_int32_value());
}

TEST(DropUnknownFieldsTest, DynamicMessage) {
  FooWithExtraFields foo_with_extra_fields;
  foo_with_extra_fields.set_int32_value(1);
  foo_with_extra_fields.set_enum_value(FooWithExtraFields::QUX);
  foo_with_extra_fields.set_extra_int32_value(2);

  google::protobuf::DynamicMessageFactory factory;
  google::protobuf::scoped_ptr<google::protobuf::Message> foo(
      factory.GetPrototype(Foo::descriptor())->New());
  ASSERT_TRUE(foo->ParseFromString(foo_with_extra_fields.SerializeAsString()));
  EXPECT_TRUE(foo->GetReflection()->GetUnknownFields(*foo).empty());

  ASSERT_TRUE(foo_with_extra_fields.ParseFromString(foo->SerializeAsString()));
  EXPECT_EQ(1, foo_with_extra_fields.int32_value());
  EXPECT_EQ(FooWithExtraFields::QUX, foo_with_extra_fields.enum_value());
  // The "extra_int32_value" field should be lost.
  EXPECT_EQ(0, foo_with_extra_fields.extra_int32_value());
}

}  // namespace protobuf
}  // namespace google
