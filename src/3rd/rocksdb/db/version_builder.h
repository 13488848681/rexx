
#pragma once
#include "rocksdb/env.h"

namespace rocksdb {

class TableCache;
class VersionStorageInfo;
class VersionEdit;
struct FileMetaData;

// A helper class so we can efficiently apply a whole sequence
// of edits to a particular state without creating intermediate
// Versions that contain full copies of the intermediate state.
class VersionBuilder {
 public:
  VersionBuilder(const EnvOptions& env_options, TableCache* table_cache,
                 VersionStorageInfo* base_vstorage);
  ~VersionBuilder();
  void CheckConsistency(VersionStorageInfo* vstorage);
  void CheckConsistencyForDeletes(VersionEdit* edit, uint64_t number,
                                  int level);
  void Apply(VersionEdit* edit);
  void SaveTo(VersionStorageInfo* vstorage);
  void LoadTableHandlers();
  void MaybeAddFile(VersionStorageInfo* vstorage, int level, FileMetaData* f);

 private:
  class Rep;
  Rep* rep_;
};

extern bool NewestFirstBySeqNo(FileMetaData* a, FileMetaData* b);
}  // namespace rocksdb
