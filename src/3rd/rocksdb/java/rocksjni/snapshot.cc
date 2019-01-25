
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/org_rocksdb_Snapshot.h"
#include "rocksdb/db.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_Snapshot
 * Method:    getSequenceNumber
 * Signature: (J)J
 */
jlong Java_org_rocksdb_Snapshot_getSequenceNumber(JNIEnv* env,
    jobject jobj, jlong jsnapshot_handle) {
  auto* snapshot = reinterpret_cast<rocksdb::Snapshot*>(
      jsnapshot_handle);
  return snapshot->GetSequenceNumber();
}
