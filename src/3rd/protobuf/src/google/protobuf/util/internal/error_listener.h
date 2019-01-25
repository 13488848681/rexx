
#ifndef GOOGLE_PROTOBUF_UTIL_CONVERTER_ERROR_LISTENER_H__
#define GOOGLE_PROTOBUF_UTIL_CONVERTER_ERROR_LISTENER_H__

#include <algorithm>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>
#include <vector>

#include <google/protobuf/stubs/callback.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/util/internal/location_tracker.h>
#include <google/protobuf/stubs/stringpiece.h>

namespace google {
namespace protobuf {
namespace util {
namespace converter {

// Interface for error listener.
class LIBPROTOBUF_EXPORT ErrorListener {
 public:
  virtual ~ErrorListener() {}

  // Reports an invalid name at the given location.
  virtual void InvalidName(const LocationTrackerInterface& loc,
                           StringPiece unknown_name, StringPiece message) = 0;

  // Reports an invalid value for a field.
  virtual void InvalidValue(const LocationTrackerInterface& loc,
                            StringPiece type_name, StringPiece value) = 0;

  // Reports a missing required field.
  virtual void MissingField(const LocationTrackerInterface& loc,
                            StringPiece missing_name) = 0;

 protected:
  ErrorListener() {}

 private:
  // Do not add any data members to this class.
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ErrorListener);
};

// An error listener that ignores all errors.
class LIBPROTOBUF_EXPORT NoopErrorListener : public ErrorListener {
 public:
  NoopErrorListener() {}
  virtual ~NoopErrorListener() {}

  virtual void InvalidName(const LocationTrackerInterface& loc,
                           StringPiece unknown_name, StringPiece message) {}

  virtual void InvalidValue(const LocationTrackerInterface& loc,
                            StringPiece type_name, StringPiece value) {}

  virtual void MissingField(const LocationTrackerInterface& loc,
                            StringPiece missing_name) {}

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(NoopErrorListener);
};


}  // namespace converter
}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_CONVERTER_ERROR_LISTENER_H__
