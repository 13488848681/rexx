
#ifndef GRPCXX_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H
#define GRPCXX_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H

#include <memory>

#include <grpc++/health_check_service_interface.h>
#include <grpc++/impl/server_builder_option.h>
#include <grpc++/support/config.h>

namespace grpc {

class HealthCheckServiceServerBuilderOption : public ServerBuilderOption {
 public:
  // The ownership of hc will be taken and transferred to the grpc server.
  // To explicitly disable default service, pass in a nullptr.
  explicit HealthCheckServiceServerBuilderOption(
      std::unique_ptr<HealthCheckServiceInterface> hc);
  ~HealthCheckServiceServerBuilderOption() override {}
  void UpdateArguments(ChannelArguments* args) override;
  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) override;

 private:
  std::unique_ptr<HealthCheckServiceInterface> hc_;
};

}  // namespace grpc

#endif  // GRPCXX_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H
