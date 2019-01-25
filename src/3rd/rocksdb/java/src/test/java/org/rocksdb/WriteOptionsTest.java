
package org.rocksdb;

import org.junit.ClassRule;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class WriteOptionsTest {

  @ClassRule
  public static final RocksMemoryResource rocksMemoryResource =
      new RocksMemoryResource();

  @Test
  public void writeOptions(){
    WriteOptions writeOptions = new WriteOptions();
    writeOptions.setDisableWAL(true);
    assertThat(writeOptions.disableWAL()).isTrue();
    writeOptions.setDisableWAL(false);
    assertThat(writeOptions.disableWAL()).isFalse();
    writeOptions.setSync(true);
    assertThat(writeOptions.sync()).isTrue();
    writeOptions.setSync(false);
    assertThat(writeOptions.sync()).isFalse();
  }
}
