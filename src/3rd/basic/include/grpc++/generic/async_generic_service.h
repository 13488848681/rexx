
#ifndef GRPCXX_GENERIC_ASYNC_GENERIC_SERVICE_H
#define GRPCXX_GENERIC_ASYNC_GENERIC_SERVICE_H

#include <grpc++/support/async_stream.h>
#include <grpc++/support/byte_buffer.h>

struct grpc_server;

namespace grpc {

typedef ServerAsyncReaderWriter<ByteBuffer, ByteBuffer>
    GenericServerAsyncReaderWriter;

class GenericServerContext final : public ServerContext {
 public:
  const grpc::string& method() const { return method_; }
  const grpc::string& host() const { return host_; }

 private:
  friend class Server;
  friend class ServerInterface;

  grpc::string method_;
  grpc::string host_;
};

class AsyncGenericService final {
 public:
  AsyncGenericService() : server_(nullptr) {}

  void RequestCall(GenericServerContext* ctx,
                   GenericServerAsyncReaderWriter* reader_writer,
                   CompletionQueue* call_cq,
                   ServerCompletionQueue* notification_cq, void* tag);

 private:
  friend class Server;
  Server* server_;
};

}  // namespace grpc

#endif  // GRPCXX_GENERIC_ASYNC_GENERIC_SERVICE_H
