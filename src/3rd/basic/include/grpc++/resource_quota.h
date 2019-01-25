
#ifndef GRPCXX_RESOURCE_QUOTA_H
#define GRPCXX_RESOURCE_QUOTA_H

struct grpc_resource_quota;

#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/grpc_library.h>

namespace grpc {

class ResourceQuota final : private GrpcLibraryCodegen {
 public:
  explicit ResourceQuota(const grpc::string& name);
  ResourceQuota();
  ~ResourceQuota();

  ResourceQuota& Resize(size_t new_size);

  grpc_resource_quota* c_resource_quota() const { return impl_; }

 private:
  ResourceQuota(const ResourceQuota& rhs);
  ResourceQuota& operator=(const ResourceQuota& rhs);

  grpc_resource_quota* const impl_;
};

}  // namespace grpc

#endif  // GRPCXX_RESOURCE_QUOTA_H
