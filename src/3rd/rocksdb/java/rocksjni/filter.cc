
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string>

#include "include/org_rocksdb_Filter.h"
#include "include/org_rocksdb_BloomFilter.h"
#include "rocksjni/portal.h"
#include "rocksdb/filter_policy.h"

/*
 * Class:     org_rocksdb_BloomFilter
 * Method:    createBloomFilter
 * Signature: (IZ)V
 */
void Java_org_rocksdb_BloomFilter_createNewBloomFilter(
    JNIEnv* env, jobject jobj, jint bits_per_key,
    jboolean use_block_base_builder) {
  rocksdb::FilterPolicy* fp = const_cast<rocksdb::FilterPolicy *>(
      rocksdb::NewBloomFilterPolicy(bits_per_key, use_block_base_builder));
  std::shared_ptr<rocksdb::FilterPolicy> *pFilterPolicy =
      new std::shared_ptr<rocksdb::FilterPolicy>;
  *pFilterPolicy = std::shared_ptr<rocksdb::FilterPolicy>(fp);
  rocksdb::FilterJni::setHandle(env, jobj, pFilterPolicy);
}

/*
 * Class:     org_rocksdb_Filter
 * Method:    disposeInternal
 * Signature: (J)V
 */
void Java_org_rocksdb_Filter_disposeInternal(
    JNIEnv* env, jobject jobj, jlong jhandle) {

  std::shared_ptr<rocksdb::FilterPolicy> *handle =
      reinterpret_cast<std::shared_ptr<rocksdb::FilterPolicy> *>(jhandle);
  handle->reset();
}
