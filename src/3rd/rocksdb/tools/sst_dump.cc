
#ifndef ROCKSDB_LITE

#include "rocksdb/sst_dump_tool.h"

int main(int argc, char** argv) {
  rocksdb::SSTDumpTool tool;
  tool.Run(argc, argv);
  return 0;
}
#else
#include <stdio.h>
int main(int argc, char** argv) {
  fprintf(stderr, "Not supported in lite mode.\n");
  return 1;
}
#endif  // ROCKSDB_LITE
