
#pragma once

#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/slice_transform.h"
#include "rocksdb/table.h"
#include "util/hash.h"
#include "format.h"

namespace rocksdb {

const uint64_t kNotValid = ULLONG_MAX;
class FilterPolicy;

// A FilterBlockBuilder is used to construct all of the filters for a
// particular Table.  It generates a single string which is stored as
// a special block in the Table.
//
// The sequence of calls to FilterBlockBuilder must match the regexp:
//      (StartBlock Add*)* Finish
//
// BlockBased/Full FilterBlock would be called in the same way.
class FilterBlockBuilder {
 public:
  explicit FilterBlockBuilder() {}
  virtual ~FilterBlockBuilder() {}

  virtual bool IsBlockBased() = 0;                    // If is blockbased filter
  virtual void StartBlock(uint64_t block_offset) = 0;  // Start new block filter
  virtual void Add(const Slice& key) = 0;      // Add a key to current filter
  virtual Slice Finish() = 0;                     // Generate Filter

 private:
  // No copying allowed
  FilterBlockBuilder(const FilterBlockBuilder&);
  void operator=(const FilterBlockBuilder&);
};

// A FilterBlockReader is used to parse filter from SST table.
// KeyMayMatch and PrefixMayMatch would trigger filter checking
//
// BlockBased/Full FilterBlock would be called in the same way.
class FilterBlockReader {
 public:
  explicit FilterBlockReader() {}
  virtual ~FilterBlockReader() {}

  virtual bool IsBlockBased() = 0;  // If is blockbased filter
  virtual bool KeyMayMatch(const Slice& key,
                           uint64_t block_offset = kNotValid) = 0;
  virtual bool PrefixMayMatch(const Slice& prefix,
                              uint64_t block_offset = kNotValid) = 0;
  virtual size_t ApproximateMemoryUsage() const = 0;

  // convert this object to a human readable form
  virtual std::string ToString() const {
    std::string error_msg("Unsupported filter \n");
    return error_msg;
  }

 private:
  // No copying allowed
  FilterBlockReader(const FilterBlockReader&);
  void operator=(const FilterBlockReader&);
};

}  // namespace rocksdb
