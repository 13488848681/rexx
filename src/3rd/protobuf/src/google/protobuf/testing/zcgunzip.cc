
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifdef _WIN32
#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif
#endif

#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using google::protobuf::io::FileInputStream;
using google::protobuf::io::GzipInputStream;

int main(int argc, const char** argv) {
  FileInputStream fin(STDIN_FILENO);
  GzipInputStream in(&fin);

  while (true) {
    const void* inptr;
    int inlen;
    bool ok;
    ok = in.Next(&inptr, &inlen);
    if (!ok) {
      break;
    }
    if (inlen > 0) {
      int err = write(STDOUT_FILENO, inptr, inlen);
      assert(err == inlen);
    }
  }

  return 0;
}
