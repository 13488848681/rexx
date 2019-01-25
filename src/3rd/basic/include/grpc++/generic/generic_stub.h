
#ifndef GRPCXX_GENERIC_GENERIC_STUB_H
#define GRPCXX_GENERIC_GENERIC_STUB_H

#include <grpc++/support/async_stream.h>
#include <grpc++/support/byte_buffer.h>

namespace grpc {

class CompletionQueue;
typedef ClientAsyncReaderWriter<ByteBuffer, ByteBuffer>
    GenericClientAsyncReaderWriter;

// Generic stubs provide a type-unsafe interface to call gRPC methods
// by name.
class GenericStub final {
 public:
  explicit GenericStub(std::shared_ptr<ChannelInterface> channel)
      : channel_(channel) {}

  // begin a call to a named method
  std::unique_ptr<GenericClientAsyncReaderWriter> Call(
      ClientContext* context, const grpc::string& method, CompletionQueue* cq,
      void* tag);

 private:
  std::shared_ptr<ChannelInterface> channel_;
};

}  // namespace grpc

#endif  // GRPCXX_GENERIC_GENERIC_STUB_H
