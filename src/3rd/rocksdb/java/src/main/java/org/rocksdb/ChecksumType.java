
package org.rocksdb;

/**
 * Checksum types used in conjunction with BlockBasedTable.
 */
public enum ChecksumType {
  /**
   * Not implemented yet.
   */
  kNoChecksum((byte) 0),
  /**
   * CRC32 Checksum
   */
  kCRC32c((byte) 1),
  /**
   * XX Hash
   */
  kxxHash((byte) 2);

  /**
   * Returns the byte value of the enumerations value
   *
   * @return byte representation
   */
  public byte getValue() {
    return value_;
  }

  private ChecksumType(byte value) {
    value_ = value;
  }

  private final byte value_;
}
