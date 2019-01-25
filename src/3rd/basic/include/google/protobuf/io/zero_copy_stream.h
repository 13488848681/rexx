
#ifndef GOOGLE_PROTOBUF_IO_ZERO_COPY_STREAM_H__
#define GOOGLE_PROTOBUF_IO_ZERO_COPY_STREAM_H__

#include <string>
#include <google/protobuf/stubs/common.h>

namespace google {

namespace protobuf {
namespace io {

// Defined in this file.
class ZeroCopyInputStream;
class ZeroCopyOutputStream;

// Abstract interface similar to an input stream but designed to minimize
// copying.
class LIBPROTOBUF_EXPORT ZeroCopyInputStream {
 public:
  inline ZeroCopyInputStream() {}
  virtual ~ZeroCopyInputStream();

  virtual bool Next(const void** data, int* size) = 0;


  virtual void BackUp(int count) = 0;

  // Skips a number of bytes.  Returns false if the end of the stream is
  // reached or some input error occurred.  In the end-of-stream case, the
  // stream is advanced to the end of the stream (so ByteCount() will return
  // the total size of the stream).
  virtual bool Skip(int count) = 0;

  // Returns the total number of bytes read since this object was created.
  virtual int64 ByteCount() const = 0;


 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ZeroCopyInputStream);
};

// Abstract interface similar to an output stream but designed to minimize
// copying.
class LIBPROTOBUF_EXPORT ZeroCopyOutputStream {
 public:
  inline ZeroCopyOutputStream() {}
  virtual ~ZeroCopyOutputStream();


  virtual bool Next(void** data, int* size) = 0;


  virtual void BackUp(int count) = 0;

  // Returns the total number of bytes written since this object was created.
  virtual int64 ByteCount() const = 0;

  // Write a given chunk of data to the output.  Some output streams may
  // implement this in a way that avoids copying. Check AllowsAliasing() before
  // calling WriteAliasedRaw(). It will GOOGLE_CHECK fail if WriteAliasedRaw() is
  // called on a stream that does not allow aliasing.
  //
  // NOTE: It is caller's responsibility to ensure that the chunk of memory
  // remains live until all of the data has been consumed from the stream.
  virtual bool WriteAliasedRaw(const void* data, int size);
  virtual bool AllowsAliasing() const { return false; }


 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ZeroCopyOutputStream);
};

}  // namespace io
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_IO_ZERO_COPY_STREAM_H__
