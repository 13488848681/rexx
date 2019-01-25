
#ifndef GRPCXX_IMPL_CODEGEN_STATUS_H
#define GRPCXX_IMPL_CODEGEN_STATUS_H

#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/status_code_enum.h>

namespace grpc {

class Status {
 public:
  /// Construct an OK instance.
  Status() : code_(StatusCode::OK) {}

  /// Construct an instance with associated \a code and \a error_message
  Status(StatusCode code, const grpc::string& error_message)
      : code_(code), error_message_(error_message) {}

  /// Construct an instance with \a code,  \a error_message and \a error_details
  Status(StatusCode code, const grpc::string& error_message,
         const grpc::string& error_details)
      : code_(code),
        error_message_(error_message),
        binary_error_details_(error_details) {}

  // Pre-defined special status objects.
  /// An OK pre-defined instance.
  static const Status& OK;
  /// A CANCELLED pre-defined instance.
  static const Status& CANCELLED;

  /// Return the instance's error code.
  StatusCode error_code() const { return code_; }
  /// Return the instance's error message.
  grpc::string error_message() const { return error_message_; }
  /// Return the (binary) error details.
  // Usually it contains a serialized google.rpc.Status proto.
  grpc::string error_details() const { return binary_error_details_; }

  /// Is the status OK?
  bool ok() const { return code_ == StatusCode::OK; }

 private:
  StatusCode code_;
  grpc::string error_message_;
  grpc::string binary_error_details_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_STATUS_H
