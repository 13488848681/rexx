
#include <vector>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/zero_copy_stream.h>

namespace google {
namespace protobuf {
namespace compiler {

class ZipWriter {
 public:
  ZipWriter(io::ZeroCopyOutputStream* raw_output);
  ~ZipWriter();

  bool Write(const string& filename, const string& contents);
  bool WriteDirectory();

 private:
  struct FileInfo {
    string name;
    uint32 offset;
    uint32 size;
    uint32 crc32;
  };

  io::ZeroCopyOutputStream* raw_output_;
  vector<FileInfo> files_;
};

}  // namespace compiler
}  // namespace protobuf
}  // namespace google
