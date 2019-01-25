
#ifndef GRPCXX_SECURITY_AUTH_METADATA_PROCESSOR_H
#define GRPCXX_SECURITY_AUTH_METADATA_PROCESSOR_H

#include <map>

#include <grpc++/security/auth_context.h>
#include <grpc++/support/status.h>
#include <grpc++/support/string_ref.h>

namespace grpc {

class AuthMetadataProcessor {
 public:
  typedef std::multimap<grpc::string_ref, grpc::string_ref> InputMetadata;
  typedef std::multimap<grpc::string, grpc::string> OutputMetadata;

  virtual ~AuthMetadataProcessor() {}

  // If this method returns true, the Process function will be scheduled in
  // a different thread from the one processing the call.
  virtual bool IsBlocking() const { return true; }

  // context is read/write: it contains the properties of the channel peer and
  // it is the job of the Process method to augment it with properties derived
  // from the passed-in auth_metadata.
  // consumed_auth_metadata needs to be filled with metadata that has been
  // consumed by the processor and will be removed from the call.
  // response_metadata is the metadata that will be sent as part of the
  // response.
  // If the return value is not Status::OK, the rpc call will be aborted with
  // the error code and error message sent back to the client.
  virtual Status Process(const InputMetadata& auth_metadata,
                         AuthContext* context,
                         OutputMetadata* consumed_auth_metadata,
                         OutputMetadata* response_metadata) = 0;
};

}  // namespace grpc

#endif  // GRPCXX_SECURITY_AUTH_METADATA_PROCESSOR_H
