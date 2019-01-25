
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>
#include <assert.h>

#include "pcrecpp_internal.h"
#include "pcre_scanner.h"

using std::vector;

namespace pcrecpp {

Scanner::Scanner()
  : data_(),
    input_(data_),
    skip_(NULL),
    should_skip_(false),
    skip_repeat_(false),
    save_comments_(false),
    comments_(NULL),
    comments_offset_(0) {
}

Scanner::Scanner(const string& in)
  : data_(in),
    input_(data_),
    skip_(NULL),
    should_skip_(false),
    skip_repeat_(false),
    save_comments_(false),
    comments_(NULL),
    comments_offset_(0) {
}

Scanner::~Scanner() {
  delete skip_;
  delete comments_;
}

void Scanner::SetSkipExpression(const char* re) {
  delete skip_;
  if (re != NULL) {
    skip_ = new RE(re);
    should_skip_ = true;
    skip_repeat_ = true;
    ConsumeSkip();
  } else {
    skip_ = NULL;
    should_skip_ = false;
    skip_repeat_ = false;
  }
}

void Scanner::Skip(const char* re) {
  delete skip_;
  if (re != NULL) {
    skip_ = new RE(re);
    should_skip_ = true;
    skip_repeat_ = false;
    ConsumeSkip();
  } else {
    skip_ = NULL;
    should_skip_ = false;
    skip_repeat_ = false;
  }
}

void Scanner::DisableSkip() {
  assert(skip_ != NULL);
  should_skip_ = false;
}

void Scanner::EnableSkip() {
  assert(skip_ != NULL);
  should_skip_ = true;
  ConsumeSkip();
}

int Scanner::LineNumber() const {
  // TODO: Make it more efficient by keeping track of the last point
  // where we computed line numbers and counting newlines since then.
  // We could use std:count, but not all systems have it. :-(
  int count = 1;
  for (const char* p = data_.data(); p < input_.data(); ++p)
    if (*p == '\n')
      ++count;
  return count;
}

int Scanner::Offset() const {
  return (int)(input_.data() - data_.c_str());
}

bool Scanner::LookingAt(const RE& re) const {
  int consumed;
  return re.DoMatch(input_, RE::ANCHOR_START, &consumed, 0, 0);
}


bool Scanner::Consume(const RE& re,
                      const Arg& arg0,
                      const Arg& arg1,
                      const Arg& arg2) {
  const bool result = re.Consume(&input_, arg0, arg1, arg2);
  if (result && should_skip_) ConsumeSkip();
  return result;
}

// helper function to consume *skip_ and honour save_comments_
void Scanner::ConsumeSkip() {
  const char* start_data = input_.data();
  while (skip_->Consume(&input_)) {
    if (!skip_repeat_) {
      // Only one skip allowed.
      break;
    }
  }
  if (save_comments_) {
    if (comments_ == NULL) {
      comments_ = new vector<StringPiece>;
    }
    // already pointing one past end, so no need to +1
    int length = (int)(input_.data() - start_data);
    if (length > 0) {
      comments_->push_back(StringPiece(start_data, length));
    }
  }
}


void Scanner::GetComments(int start, int end, vector<StringPiece> *ranges) {
  // short circuit out if we've not yet initialized comments_
  // (e.g., when save_comments is false)
  if (!comments_) {
    return;
  }
  // TODO: if we guarantee that comments_ will contain StringPieces
  // that are ordered by their start, then we can do a binary search
  // for the first StringPiece at or past start and then scan for the
  // ones contained in the range, quit early (use equal_range or
  // lower_bound)
  for (vector<StringPiece>::const_iterator it = comments_->begin();
       it != comments_->end(); ++it) {
    if ((it->data() >= data_.c_str() + start &&
         it->data() + it->size() <= data_.c_str() + end)) {
      ranges->push_back(*it);
    }
  }
}


void Scanner::GetNextComments(vector<StringPiece> *ranges) {
  // short circuit out if we've not yet initialized comments_
  // (e.g., when save_comments is false)
  if (!comments_) {
    return;
  }
  for (vector<StringPiece>::const_iterator it =
         comments_->begin() + comments_offset_;
       it != comments_->end(); ++it) {
    ranges->push_back(*it);
    ++comments_offset_;
  }
}

}   // namespace pcrecpp
