
#ifndef GRPCXX_IMPL_CODEGEN_STATUS_CODE_ENUM_H
#define GRPCXX_IMPL_CODEGEN_STATUS_CODE_ENUM_H

namespace grpc {

enum StatusCode {
  /// Not an error; returned on success.
  OK = 0,

  /// The operation was cancelled (typically by the caller).
  CANCELLED = 1,

  UNKNOWN = 2,

  INVALID_ARGUMENT = 3,

  DEADLINE_EXCEEDED = 4,

  /// Some requested entity (e.g., file or directory) was not found.
  NOT_FOUND = 5,

  /// Some entity that we attempted to create (e.g., file or directory) already
  /// exists.
  ALREADY_EXISTS = 6,

  PERMISSION_DENIED = 7,

  /// The request does not have valid authentication credentials for the
  /// operation.
  UNAUTHENTICATED = 16,

  /// Some resource has been exhausted, perhaps a per-user quota, or perhaps the
  /// entire file system is out of space.
  RESOURCE_EXHAUSTED = 8,

  FAILED_PRECONDITION = 9,

  ABORTED = 10,

  OUT_OF_RANGE = 11,

  /// Operation is not implemented or not supported/enabled in this service.
  UNIMPLEMENTED = 12,

  /// Internal errors. Means some invariants expected by underlying System has
  /// been broken. If you see one of these errors, Something is very broken.
  INTERNAL = 13,

  /// The service is currently unavailable. This is a most likely a transient
  /// condition and may be corrected by retrying with a backoff.
  ///
  /// See litmus test above for deciding between FAILED_PRECONDITION, ABORTED,
  /// and UNAVAILABLE.
  UNAVAILABLE = 14,

  /// Unrecoverable data loss or corruption.
  DATA_LOSS = 15,

  /// Force users to include a default branch:
  DO_NOT_USE = -1
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_STATUS_CODE_ENUM_H
