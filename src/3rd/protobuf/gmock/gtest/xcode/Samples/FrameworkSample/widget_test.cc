
#include <string>
#include "gtest/gtest.h"

#include <Widget/widget.h>

// This test verifies that the constructor sets the internal state of the
// Widget class correctly.
TEST(WidgetInitializerTest, TestConstructor) {
  Widget widget(1.0f, "name");
  EXPECT_FLOAT_EQ(1.0f, widget.GetFloatValue());
  EXPECT_EQ(std::string("name"), widget.GetStringValue());
}

// This test verifies the conversion of the float and string values to int and
// char*, respectively.
TEST(WidgetInitializerTest, TestConversion) {
  Widget widget(1.0f, "name");
  EXPECT_EQ(1, widget.GetIntValue());

  size_t max_size = 128;
  char buffer[max_size];
  widget.GetCharPtrValue(buffer, max_size);
  EXPECT_STREQ("name", buffer);
}

// Use the Google Test main that is linked into the framework. It does something
// like this:
// int main(int argc, char** argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
