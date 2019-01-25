
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_LOCATION_TRACKER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_LOCATION_TRACKER_H__

#include <string>

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

// LocationTrackerInterface is an interface for classes that track
// the location information for the purpose of error reporting.
class LIBPROTOBUF_EXPORT LocationTrackerInterface {
 public:
  virtual ~LocationTrackerInterface() {}

  // Returns the object location as human readable string.
  virtual string ToString() const = 0;

 protected:
  LocationTrackerInterface() {}

 private:
  // Please do not add any data members to this class.
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(LocationTrackerInterface);
};

}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_LOCATION_TRACKER_H__
