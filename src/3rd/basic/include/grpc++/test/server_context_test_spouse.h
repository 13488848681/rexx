
#ifndef GRPCXX_TEST_SERVER_CONTEXT_TEST_SPOUSE_H
#define GRPCXX_TEST_SERVER_CONTEXT_TEST_SPOUSE_H

#include <map>

#include <grpc++/server_context.h>

namespace grpc {
namespace testing {

// A test-only class to access private members and methods of ServerContext.
class ServerContextTestSpouse {
 public:
  explicit ServerContextTestSpouse(ServerContext* ctx) : ctx_(ctx) {}

  // Inject client metadata to the ServerContext for the test. The test spouse
  // must be alive when ServerContext::client_metadata is called.
  void AddClientMetadata(const grpc::string& key, const grpc::string& value) {
    client_metadata_storage_.insert(
        std::pair<grpc::string, grpc::string>(key, value));
    ctx_->client_metadata_.map()->clear();
    for (auto iter = client_metadata_storage_.begin();
         iter != client_metadata_storage_.end(); ++iter) {
      ctx_->client_metadata_.map()->insert(
          std::pair<grpc::string_ref, grpc::string_ref>(
              iter->first.c_str(),
              grpc::string_ref(iter->second.data(), iter->second.size())));
    }
  }

  std::multimap<grpc::string, grpc::string> GetInitialMetadata() const {
    return ctx_->initial_metadata_;
  }

  std::multimap<grpc::string, grpc::string> GetTrailingMetadata() const {
    return ctx_->trailing_metadata_;
  }

 private:
  ServerContext* ctx_;  // not owned
  std::multimap<grpc::string, grpc::string> client_metadata_storage_;
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPCXX_TEST_SERVER_CONTEXT_TEST_SPOUSE_H
