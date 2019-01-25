
#include "db/version_edit.h"
#include "util/testharness.h"

namespace rocksdb {

static void TestEncodeDecode(const VersionEdit& edit) {
  std::string encoded, encoded2;
  edit.EncodeTo(&encoded);
  VersionEdit parsed;
  Status s = parsed.DecodeFrom(encoded);
  ASSERT_TRUE(s.ok()) << s.ToString();
  parsed.EncodeTo(&encoded2);
  ASSERT_EQ(encoded, encoded2);
}

class VersionEditTest : public testing::Test {};

TEST_F(VersionEditTest, EncodeDecode) {
  static const uint64_t kBig = 1ull << 50;
  static const uint32_t kBig32Bit = 1ull << 30;

  VersionEdit edit;
  for (int i = 0; i < 4; i++) {
    TestEncodeDecode(edit);
    edit.AddFile(3, kBig + 300 + i, kBig32Bit + 400 + i, 0,
                 InternalKey("foo", kBig + 500 + i, kTypeValue),
                 InternalKey("zoo", kBig + 600 + i, kTypeDeletion),
                 kBig + 500 + i, kBig + 600 + i);
    edit.DeleteFile(4, kBig + 700 + i);
  }

  edit.SetComparatorName("foo");
  edit.SetLogNumber(kBig + 100);
  edit.SetNextFile(kBig + 200);
  edit.SetLastSequence(kBig + 1000);
  TestEncodeDecode(edit);
}

TEST_F(VersionEditTest, EncodeEmptyFile) {
  VersionEdit edit;
  edit.AddFile(0, 0, 0, 0,
               InternalKey(),
               InternalKey(),
               0, 0);
  std::string buffer;
  ASSERT_TRUE(!edit.EncodeTo(&buffer));
}

TEST_F(VersionEditTest, ColumnFamilyTest) {
  VersionEdit edit;
  edit.SetColumnFamily(2);
  edit.AddColumnFamily("column_family");
  edit.SetMaxColumnFamily(5);
  TestEncodeDecode(edit);

  edit.Clear();
  edit.SetColumnFamily(3);
  edit.DropColumnFamily();
  TestEncodeDecode(edit);
}

}  // namespace rocksdb

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
