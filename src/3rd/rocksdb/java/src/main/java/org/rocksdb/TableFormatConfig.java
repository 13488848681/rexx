
package org.rocksdb;

/**
 * TableFormatConfig is used to config the internal Table format of a RocksDB.
 * To make a RocksDB to use a specific Table format, its associated
 * TableFormatConfig should be properly set and passed into Options via
 * Options.setTableFormatConfig() and open the db using that Options.
 */
public abstract class TableFormatConfig {
  /**
   * <p>This function should only be called by Options.setTableFormatConfig(),
   * which will create a c++ shared-pointer to the c++ TableFactory
   * that associated with the Java TableFormatConfig.</p>
   *
   * @return native handle address to native table instance.
   */
  abstract protected long newTableFactoryHandle();
}
