
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_LOCATION_TRACKER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_LOCATION_TRACKER_H__

#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/util/internal/location_tracker.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

// An empty concrete implementation of LocationTrackerInterface.
class ObjectLocationTracker : public LocationTrackerInterface {
 public:
  // Creates an empty location tracker.
  ObjectLocationTracker() {}

  virtual ~ObjectLocationTracker() {}

  // Returns empty because nothing is tracked.
  virtual string ToString() const { return ""; }

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ObjectLocationTracker);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_OBJECT_LOCATION_TRACKER_H__
