
package org.rocksdb;

/**
 * MergeOperator holds an operator to be applied when compacting
 * two merge operands held under the same key in order to obtain a single
 * value.
 */
public interface MergeOperator {
    long newMergeOperatorHandle();
}
