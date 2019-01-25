
#ifndef GOOGLE_PROTOBUF_TESTING_FILE_H__
#define GOOGLE_PROTOBUF_TESTING_FILE_H__

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {

const int DEFAULT_FILE_MODE = 0777;

// Protocol buffer code only uses a couple static methods of File, and only
// in tests.
class File {
 public:
  // Check if the file exists.
  static bool Exists(const string& name);

  // Read an entire file to a string.  Return true if successful, false
  // otherwise.
  static bool ReadFileToString(const string& name, string* output);

  // Same as above, but crash on failure.
  static void ReadFileToStringOrDie(const string& name, string* output);

  // Create a file and write a string to it.
  static bool WriteStringToFile(const string& contents,
                                const string& name);

  // Same as above, but crash on failure.
  static void WriteStringToFileOrDie(const string& contents,
                                     const string& name);

  // Create a directory.
  static bool CreateDir(const string& name, int mode);

  // Create a directory and all parent directories if necessary.
  static bool RecursivelyCreateDir(const string& path, int mode);

  // If "name" is a file, we delete it.  If it is a directory, we
  // call DeleteRecursively() for each file or directory (other than
  // dot and double-dot) within it, and then delete the directory itself.
  // The "dummy" parameters have a meaning in the original version of this
  // method but they are not used anywhere in protocol buffers.
  static void DeleteRecursively(const string& name,
                                void* dummy1, void* dummy2);

  // Change working directory to given directory.
  static bool ChangeWorkingDirectory(const string& new_working_directory);

  static bool GetContents(
      const string& name, string* output, bool /*is_default*/) {
    return ReadFileToString(name, output);
  }

  static bool SetContents(
      const string& name, const string& contents, bool /*is_default*/) {
    return WriteStringToFile(contents, name);
  }

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(File);
};

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_TESTING_FILE_H__
