
package org.rocksdb;

/**
 * Builtin RocksDB comparators
 *
 * <ol>
 *   <li>BYTEWISE_COMPARATOR - Sorts all keys in ascending bytewise
 *   order.</li>
 *   <li>REVERSE_BYTEWISE_COMPARATOR - Sorts all keys in descending bytewise
 *   order</li>
 * </ol>
 */
public enum BuiltinComparator {
  BYTEWISE_COMPARATOR, REVERSE_BYTEWISE_COMPARATOR
}
