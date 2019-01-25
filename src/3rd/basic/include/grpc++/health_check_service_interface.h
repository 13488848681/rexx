
#ifndef GRPCXX_HEALTH_CHECK_SERVICE_INTERFACE_H
#define GRPCXX_HEALTH_CHECK_SERVICE_INTERFACE_H

#include <grpc++/support/config.h>

namespace grpc {

const char kHealthCheckServiceInterfaceArg[] =
    "grpc.health_check_service_interface";

// The gRPC server uses this interface to expose the health checking service
// without depending on protobuf.
class HealthCheckServiceInterface {
 public:
  virtual ~HealthCheckServiceInterface() {}

  // Set or change the serving status of the given service_name.
  virtual void SetServingStatus(const grpc::string& service_name,
                                bool serving) = 0;
  // Apply to all registered service names.
  virtual void SetServingStatus(bool serving) = 0;
};

// Enable/disable the default health checking service. This applies to all C++
// servers created afterwards. For each server, user can override the default
// with a HealthCheckServiceServerBuilderOption.
// NOT thread safe.
void EnableDefaultHealthCheckService(bool enable);

// NOT thread safe.
bool DefaultHealthCheckServiceEnabled();

}  // namespace grpc

#endif  // GRPCXX_HEALTH_CHECK_SERVICE_INTERFACE_H
