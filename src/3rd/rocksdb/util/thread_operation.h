
#pragma once

#include "include/rocksdb/thread_status.h"

#include <string>

namespace rocksdb {

#if ROCKSDB_USING_THREAD_STATUS

// The structure that describes a major thread operation.
struct OperationInfo {
  const ThreadStatus::OperationType type;
  const std::string name;
};

// The global operation table.
//
// When updating a status of a thread, the pointer of the OperationInfo
// of the current ThreadStatusData will be pointing to one of the
// rows in this global table.
//
// Note that it's not designed to be constant as in the future we
// might consider adding global count to the OperationInfo.
static OperationInfo global_operation_table[] = {
  {ThreadStatus::OP_UNKNOWN, ""},
  {ThreadStatus::OP_COMPACTION, "Compaction"},
  {ThreadStatus::OP_FLUSH, "Flush"}
};

struct OperationStageInfo {
  const ThreadStatus::OperationStage stage;
  const std::string name;
};

// A table maintains the mapping from stage type to stage string.
// Note that the string must be changed accordingly when the
// associated function name changed.
static OperationStageInfo global_op_stage_table[] = {
  {ThreadStatus::STAGE_UNKNOWN, ""},
  {ThreadStatus::STAGE_FLUSH_RUN,
      "FlushJob::Run"},
  {ThreadStatus::STAGE_FLUSH_WRITE_L0,
      "FlushJob::WriteLevel0Table"},
  {ThreadStatus::STAGE_COMPACTION_PREPARE,
      "CompactionJob::Prepare"},
  {ThreadStatus::STAGE_COMPACTION_RUN,
      "CompactionJob::Run"},
  {ThreadStatus::STAGE_COMPACTION_PROCESS_KV,
      "CompactionJob::ProcessKeyValueCompaction"},
  {ThreadStatus::STAGE_COMPACTION_FILTER_V2,
      "CompactionJob::CallCompactionFilterV2"},
  {ThreadStatus::STAGE_COMPACTION_INSTALL,
      "CompactionJob::Install"},
  {ThreadStatus::STAGE_COMPACTION_SYNC_FILE,
      "CompactionJob::FinishCompactionOutputFile"},
  {ThreadStatus::STAGE_PICK_MEMTABLES_TO_FLUSH,
      "MemTableList::PickMemtablesToFlush"},
  {ThreadStatus::STAGE_MEMTABLE_ROLLBACK,
      "MemTableList::RollbackMemtableFlush"},
  {ThreadStatus::STAGE_MEMTABLE_INSTALL_FLUSH_RESULTS,
      "MemTableList::InstallMemtableFlushResults"},
};

// The structure that describes a state.
struct StateInfo {
  const ThreadStatus::StateType type;
  const std::string name;
};

// The global state table.
//
// When updating a status of a thread, the pointer of the StateInfo
// of the current ThreadStatusData will be pointing to one of the
// rows in this global table.
static StateInfo global_state_table[] = {
  {ThreadStatus::STATE_UNKNOWN, ""},
  {ThreadStatus::STATE_MUTEX_WAIT, "Mutex Wait"},
};

#else

struct OperationInfo {
};

struct StateInfo {
};

#endif  // ROCKSDB_USING_THREAD_STATUS
}  // namespace rocksdb
