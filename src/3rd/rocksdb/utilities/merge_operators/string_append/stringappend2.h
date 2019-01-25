
#pragma once
#include <deque>
#include <string>

#include "rocksdb/merge_operator.h"
#include "rocksdb/slice.h"

namespace rocksdb {

class StringAppendTESTOperator : public MergeOperator {
 public:
  // Constructor with delimiter
  explicit StringAppendTESTOperator(char delim_char);

  virtual bool FullMerge(const Slice& key,
                         const Slice* existing_value,
                         const std::deque<std::string>& operand_sequence,
                         std::string* new_value,
                         Logger* logger) const override;

  virtual bool PartialMergeMulti(const Slice& key,
                                 const std::deque<Slice>& operand_list,
                                 std::string* new_value, Logger* logger) const
      override;

  virtual const char* Name() const override;

 private:
  // A version of PartialMerge that actually performs "partial merging".
  // Use this to simulate the exact behaviour of the StringAppendOperator.
  bool _AssocPartialMergeMulti(const Slice& key,
                               const std::deque<Slice>& operand_list,
                               std::string* new_value, Logger* logger) const;

  char delim_;         // The delimiter is inserted between elements

};

} // namespace rocksdb
