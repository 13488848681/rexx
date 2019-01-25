
package org.rocksdb;

/**
 * Base class for comparators which will receive
 * ByteBuffer based access via org.rocksdb.DirectSlice
 * in their compare method implementation.
 *
 * ByteBuffer based slices perform better when large keys
 * are involved. When using smaller keys consider
 * using @see org.rocksdb.Comparator
 */
public abstract class DirectComparator extends AbstractComparator<DirectSlice> {
  public DirectComparator(final ComparatorOptions copt) {
    super();
    createNewDirectComparator0(copt.nativeHandle_);
  }

  private native void createNewDirectComparator0(final long comparatorOptionsHandle);
}
