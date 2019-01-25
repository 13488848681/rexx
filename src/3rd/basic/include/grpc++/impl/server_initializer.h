
#ifndef GRPCXX_IMPL_SERVER_INITIALIZER_H
#define GRPCXX_IMPL_SERVER_INITIALIZER_H

#include <memory>
#include <vector>

#include <grpc++/server.h>

namespace grpc {

class Server;
class Service;

class ServerInitializer {
 public:
  ServerInitializer(Server* server) : server_(server) {}

  bool RegisterService(std::shared_ptr<Service> service) {
    if (!server_->RegisterService(nullptr, service.get())) {
      return false;
    }
    default_services_.push_back(service);
    return true;
  }

  const std::vector<grpc::string>* GetServiceList() {
    return &server_->services_;
  }

 private:
  Server* server_;
  std::vector<std::shared_ptr<Service> > default_services_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_SERVER_INITIALIZER_H
