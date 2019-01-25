
package org.rocksdb;

import org.junit.ClassRule;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class RocksEnvTest {

  @ClassRule
  public static final RocksMemoryResource rocksMemoryResource =
      new RocksMemoryResource();

  @Test
  public void rocksEnv(){
    Env rocksEnv = RocksEnv.getDefault();
    rocksEnv.setBackgroundThreads(5);
    // default rocksenv will always return zero for flush pool
    // no matter what was set via setBackgroundThreads
    assertThat(rocksEnv.getThreadPoolQueueLen(RocksEnv.FLUSH_POOL)).
        isEqualTo(0);
    rocksEnv.setBackgroundThreads(5, RocksEnv.FLUSH_POOL);
    // default rocksenv will always return zero for flush pool
    // no matter what was set via setBackgroundThreads
    assertThat(rocksEnv.getThreadPoolQueueLen(RocksEnv.FLUSH_POOL)).
        isEqualTo(0);
    rocksEnv.setBackgroundThreads(5, RocksEnv.COMPACTION_POOL);
    // default rocksenv will always return zero for compaction pool
    // no matter what was set via setBackgroundThreads
    assertThat(rocksEnv.getThreadPoolQueueLen(RocksEnv.COMPACTION_POOL)).
        isEqualTo(0);
  }
}
