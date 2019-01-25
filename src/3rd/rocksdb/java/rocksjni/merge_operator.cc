
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string>
#include <memory>

#include "include/org_rocksdb_StringAppendOperator.h"
#include "rocksjni/portal.h"
#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/statistics.h"
#include "rocksdb/memtablerep.h"
#include "rocksdb/table.h"
#include "rocksdb/slice_transform.h"
#include "rocksdb/merge_operator.h"
#include "utilities/merge_operators.h"

/*
 * Class:     org_rocksdb_StringAppendOperator
 * Method:    newMergeOperatorHandle
 * Signature: ()J
 */
jlong Java_org_rocksdb_StringAppendOperator_newMergeOperatorHandleImpl
(JNIEnv* env, jobject jobj) {
  std::shared_ptr<rocksdb::MergeOperator> *op =
    new std::shared_ptr<rocksdb::MergeOperator>();
  *op = rocksdb::MergeOperators::CreateFromStringId("stringappend");
  return reinterpret_cast<jlong>(op);
}
