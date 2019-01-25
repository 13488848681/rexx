
package org.rocksdb.util;

import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class SizeUnitTest {

  public static final long COMPUTATION_UNIT = 1024L;

  @Test
  public void sizeUnit() {
    assertThat(SizeUnit.KB).isEqualTo(COMPUTATION_UNIT);
    assertThat(SizeUnit.MB).isEqualTo(
        SizeUnit.KB * COMPUTATION_UNIT);
    assertThat(SizeUnit.GB).isEqualTo(
        SizeUnit.MB * COMPUTATION_UNIT);
    assertThat(SizeUnit.TB).isEqualTo(
        SizeUnit.GB * COMPUTATION_UNIT);
    assertThat(SizeUnit.PB).isEqualTo(
        SizeUnit.TB * COMPUTATION_UNIT);
  }
}
