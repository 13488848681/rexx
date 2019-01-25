
#ifndef GOOGLE_PROTOBUF_GOOGLETEST_H__
#define GOOGLE_PROTOBUF_GOOGLETEST_H__

#include <map>
#include <vector>
#include <google/protobuf/stubs/common.h>

// Disable death tests if we use exceptions in CHECK().
#if !PROTOBUF_USE_EXCEPTIONS && defined(GTEST_HAS_DEATH_TEST)
#define PROTOBUF_HAS_DEATH_TEST
#endif

namespace google {
namespace protobuf {

// When running unittests, get the directory containing the source code.
string TestSourceDir();

// When running unittests, get a directory where temporary files may be
// placed.
string TestTempDir();

// Capture all text written to stdout or stderr.
void CaptureTestStdout();
void CaptureTestStderr();

// Stop capturing stdout or stderr and return the text captured.
string GetCapturedTestStdout();
string GetCapturedTestStderr();

// For use with ScopedMemoryLog::GetMessages().  Inside Google the LogLevel
// constants don't have the LOGLEVEL_ prefix, so the code that used
// ScopedMemoryLog refers to LOGLEVEL_ERROR as just ERROR.
#undef ERROR  // defend against promiscuous windows.h
static const LogLevel ERROR = LOGLEVEL_ERROR;
static const LogLevel WARNING = LOGLEVEL_WARNING;

// Receives copies of all LOG(ERROR) messages while in scope.  Sample usage:
//   {
//     ScopedMemoryLog log;  // constructor registers object as a log sink
//     SomeRoutineThatMayLogMessages();
//     const vector<string>& warnings = log.GetMessages(ERROR);
//   }  // destructor unregisters object as a log sink
// This is a dummy implementation which covers only what is used by protocol
// buffer unit tests.
class ScopedMemoryLog {
 public:
  ScopedMemoryLog();
  virtual ~ScopedMemoryLog();

  // Fetches all messages with the given severity level.
  const vector<string>& GetMessages(LogLevel error);

 private:
  map<LogLevel, vector<string> > messages_;
  LogHandler* old_handler_;

  static void HandleLog(LogLevel level, const char* filename, int line,
                        const string& message);

  static ScopedMemoryLog* active_log_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ScopedMemoryLog);
};

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_GOOGLETEST_H__
