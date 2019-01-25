
package org.rocksdb;

import org.junit.Test;


public class CompressionOptionsTest
{
  @Test
  public void getCompressionType() {
    for (CompressionType compressionType : CompressionType.values()) {
      String libraryName = compressionType.getLibraryName();
      compressionType.equals(CompressionType.getCompressionType(
          libraryName));
    }
  }
}
