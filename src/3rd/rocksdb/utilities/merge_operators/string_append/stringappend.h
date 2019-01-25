
#pragma once
#include "rocksdb/merge_operator.h"
#include "rocksdb/slice.h"

namespace rocksdb {

class StringAppendOperator : public AssociativeMergeOperator {
 public:
  StringAppendOperator(char delim_char);    /// Constructor: specify delimiter

  virtual bool Merge(const Slice& key,
                     const Slice* existing_value,
                     const Slice& value,
                     std::string* new_value,
                     Logger* logger) const override;

  virtual const char* Name() const override;

 private:
  char delim_;         // The delimiter is inserted between elements

};

} // namespace rocksdb

