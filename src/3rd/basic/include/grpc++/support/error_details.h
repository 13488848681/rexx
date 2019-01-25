
#ifndef GRPCXX_SUPPORT_ERROR_DETAILS_H
#define GRPCXX_SUPPORT_ERROR_DETAILS_H

#include <grpc++/support/status.h>

namespace google {
namespace rpc {
class Status;
}  // namespace rpc
}  // namespace google

namespace grpc {

// Maps a grpc::Status to a google::rpc::Status.
// The given \a to object will be cleared.
// On success, returns status with OK.
// Returns status with INVALID_ARGUMENT, if failed to deserialize.
// Returns status with FAILED_PRECONDITION, if \a to is nullptr.
Status ExtractErrorDetails(const Status& from, ::google::rpc::Status* to);

// Maps google::rpc::Status to a grpc::Status.
// Returns OK on success.
// Returns status with FAILED_PRECONDITION if \a to is nullptr.
Status SetErrorDetails(const ::google::rpc::Status& from, Status* to);

}  // namespace grpc

#endif  // GRPCXX_SUPPORT_ERROR_DETAILS_H
