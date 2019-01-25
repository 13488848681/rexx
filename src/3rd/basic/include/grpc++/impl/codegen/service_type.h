
#ifndef GRPCXX_IMPL_CODEGEN_SERVICE_TYPE_H
#define GRPCXX_IMPL_CODEGEN_SERVICE_TYPE_H

#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/core_codegen_interface.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/serialization_traits.h>
#include <grpc++/impl/codegen/server_interface.h>
#include <grpc++/impl/codegen/status.h>

namespace grpc {

class Call;
class CompletionQueue;
class Server;
class ServerInterface;
class ServerCompletionQueue;
class ServerContext;

class ServerAsyncStreamingInterface {
 public:
  virtual ~ServerAsyncStreamingInterface() {}

  virtual void SendInitialMetadata(void* tag) = 0;

 private:
  friend class ServerInterface;
  virtual void BindCall(Call* call) = 0;
};

class Service {
 public:
  Service() : server_(nullptr) {}
  virtual ~Service() {}

  bool has_async_methods() const {
    for (auto it = methods_.begin(); it != methods_.end(); ++it) {
      if (*it && (*it)->handler() == nullptr) {
        return true;
      }
    }
    return false;
  }

  bool has_synchronous_methods() const {
    for (auto it = methods_.begin(); it != methods_.end(); ++it) {
      if (*it && (*it)->handler() != nullptr) {
        return true;
      }
    }
    return false;
  }

  bool has_generic_methods() const {
    for (auto it = methods_.begin(); it != methods_.end(); ++it) {
      if (it->get() == nullptr) {
        return true;
      }
    }
    return false;
  }

 protected:
  template <class Message>
  void RequestAsyncUnary(int index, ServerContext* context, Message* request,
                         ServerAsyncStreamingInterface* stream,
                         CompletionQueue* call_cq,
                         ServerCompletionQueue* notification_cq, void* tag) {
    server_->RequestAsyncCall(methods_[index].get(), context, stream, call_cq,
                              notification_cq, tag, request);
  }
  void RequestAsyncClientStreaming(int index, ServerContext* context,
                                   ServerAsyncStreamingInterface* stream,
                                   CompletionQueue* call_cq,
                                   ServerCompletionQueue* notification_cq,
                                   void* tag) {
    server_->RequestAsyncCall(methods_[index].get(), context, stream, call_cq,
                              notification_cq, tag);
  }
  template <class Message>
  void RequestAsyncServerStreaming(int index, ServerContext* context,
                                   Message* request,
                                   ServerAsyncStreamingInterface* stream,
                                   CompletionQueue* call_cq,
                                   ServerCompletionQueue* notification_cq,
                                   void* tag) {
    server_->RequestAsyncCall(methods_[index].get(), context, stream, call_cq,
                              notification_cq, tag, request);
  }
  void RequestAsyncBidiStreaming(int index, ServerContext* context,
                                 ServerAsyncStreamingInterface* stream,
                                 CompletionQueue* call_cq,
                                 ServerCompletionQueue* notification_cq,
                                 void* tag) {
    server_->RequestAsyncCall(methods_[index].get(), context, stream, call_cq,
                              notification_cq, tag);
  }

  void AddMethod(RpcServiceMethod* method) { methods_.emplace_back(method); }

  void MarkMethodAsync(int index) {
    GPR_CODEGEN_ASSERT(
        methods_[index].get() != nullptr &&
        "Cannot mark the method as 'async' because it has already been "
        "marked as 'generic'.");
    methods_[index]->ResetHandler();
  }

  void MarkMethodGeneric(int index) {
    GPR_CODEGEN_ASSERT(
        methods_[index]->handler() != nullptr &&
        "Cannot mark the method as 'generic' because it has already been "
        "marked as 'async'.");
    methods_[index].reset();
  }

  void MarkMethodStreamed(int index, MethodHandler* streamed_method) {
    GPR_CODEGEN_ASSERT(methods_[index] && methods_[index]->handler() &&
                       "Cannot mark an async or generic method Streamed");
    methods_[index]->SetHandler(streamed_method);

    methods_[index]->SetMethodType(::grpc::RpcMethod::BIDI_STREAMING);
  }

 private:
  friend class Server;
  friend class ServerInterface;
  ServerInterface* server_;
  std::vector<std::unique_ptr<RpcServiceMethod>> methods_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_SERVICE_TYPE_H
