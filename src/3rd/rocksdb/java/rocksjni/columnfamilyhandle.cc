
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include "include/org_rocksdb_ColumnFamilyHandle.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_ColumnFamilyHandle
 * Method:    disposeInternal
 * Signature: (J)V
 */
void Java_org_rocksdb_ColumnFamilyHandle_disposeInternal(
    JNIEnv* env, jobject jobj, jlong handle) {
  auto it = reinterpret_cast<rocksdb::ColumnFamilyHandle*>(handle);
  delete it;
}
