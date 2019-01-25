
package org.rocksdb;

/**
 * IndexType used in conjunction with BlockBasedTable.
 */
public enum IndexType {
  /**
   * A space efficient index block that is optimized for
   * binary-search-based index.
   */
  kBinarySearch((byte) 0),
  /**
   * The hash index, if enabled, will do the hash lookup when
   * {@code Options.prefix_extractor} is provided.
   */
  kHashSearch((byte) 1);

  /**
   * Returns the byte value of the enumerations value
   *
   * @return byte representation
   */
  public byte getValue() {
    return value_;
  }

  private IndexType(byte value) {
    value_ = value;
  }

  private final byte value_;
}
