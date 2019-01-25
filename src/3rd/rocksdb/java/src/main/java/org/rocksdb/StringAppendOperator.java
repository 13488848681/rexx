
package org.rocksdb;

/**
 * StringAppendOperator is a merge operator that concatenates
 * two strings.
 */
public class StringAppendOperator implements MergeOperator {
    @Override public long newMergeOperatorHandle() {
        return newMergeOperatorHandleImpl();
    }
    private native long newMergeOperatorHandleImpl();
}
