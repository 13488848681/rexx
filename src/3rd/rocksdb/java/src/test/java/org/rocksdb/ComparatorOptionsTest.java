
package org.rocksdb;

import org.junit.ClassRule;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ComparatorOptionsTest {

  @ClassRule
  public static final RocksMemoryResource rocksMemoryResource =
      new RocksMemoryResource();

  @Test
  public void comparatorOptions() {
    final ComparatorOptions copt = new ComparatorOptions();

    assertThat(copt).isNotNull();

    { // UseAdaptiveMutex test
      copt.setUseAdaptiveMutex(true);
      assertThat(copt.useAdaptiveMutex()).isTrue();

      copt.setUseAdaptiveMutex(false);
      assertThat(copt.useAdaptiveMutex()).isFalse();
    }

    copt.dispose();
  }
}
