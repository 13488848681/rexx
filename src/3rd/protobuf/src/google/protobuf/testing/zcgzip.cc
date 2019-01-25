
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

using google::protobuf::io::FileOutputStream;
using google::protobuf::io::GzipOutputStream;

int main(int argc, const char** argv) {
  FileOutputStream fout(STDOUT_FILENO);
  GzipOutputStream out(&fout);
  int readlen;

  while (true) {
    void* outptr;
    int outlen;
    bool ok;
    do {
      ok = out.Next(&outptr, &outlen);
      if (!ok) {
        break;
      }
    } while (outlen <= 0);
    readlen = read(STDIN_FILENO, outptr, outlen);
    if (readlen <= 0) {
      out.BackUp(outlen);
      break;
    }
    if (readlen < outlen) {
      out.BackUp(outlen - readlen);
    }
  }

  return 0;
}
