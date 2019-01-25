
#include <google/protobuf/arena_test_util.h>
#include <google/protobuf/map_lite_test_util.h>
#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace {

TEST(LiteArenaTest, MapNoHeapAllocation) {
  // Allocate a large initial block to avoid mallocs during hooked test.
  std::vector<char> arena_block(128 * 1024);
  google::protobuf::ArenaOptions options;
  options.initial_block = &arena_block[0];
  options.initial_block_size = arena_block.size();
  google::protobuf::Arena arena(options);
  string data;
  data.reserve(128 * 1024);

  {
    // TODO(teboring): Enable no heap check when ArenaStringPtr is used in
    // Map.
    // google::protobuf::internal::NoHeapChecker no_heap;

    protobuf_unittest::TestArenaMapLite* from =
        google::protobuf::Arena::CreateMessage<protobuf_unittest::TestArenaMapLite>(&arena);
    google::protobuf::MapLiteTestUtil::SetArenaMapFields(from);
    from->SerializeToString(&data);

    protobuf_unittest::TestArenaMapLite* to =
        google::protobuf::Arena::CreateMessage<protobuf_unittest::TestArenaMapLite>(&arena);
    to->ParseFromString(data);
    google::protobuf::MapLiteTestUtil::ExpectArenaMapFieldsSet(*to);
  }
}

TEST(LiteArenaTest, UnknownFieldMemLeak) {
  google::protobuf::Arena arena;
  protobuf_unittest::ForeignMessageArenaLite* message =
      google::protobuf::Arena::CreateMessage<protobuf_unittest::ForeignMessageArenaLite>(
          &arena);
  string data = "\012\000";
  int original_capacity = data.capacity();
  while (data.capacity() <= original_capacity) {
    data.append("a");
  }
  data[1] = data.size() - 2;
  message->ParseFromString(data);
}

}  // namespace
}  // namespace protobuf
}  // namespace google
