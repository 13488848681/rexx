
#ifndef GOOGLE_PROTOBUF_ARENA_TEST_UTIL_H__
#define GOOGLE_PROTOBUF_ARENA_TEST_UTIL_H__


namespace google {
namespace protobuf {
namespace internal {

class NoHeapChecker {
 public:
  NoHeapChecker() {
    capture_alloc.Hook();
  }
  ~NoHeapChecker();
 private:
  class NewDeleteCapture {
   public:
    // TOOD(xiaofeng): Implement this for opensource protobuf.
    void Hook() {}
    void Unhook() {}
    int alloc_count() { return 0; }
    int free_count() { return 0; }
  } capture_alloc;
};

}  // namespace internal
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_ARENA_TEST_UTIL_H__
