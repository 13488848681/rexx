
#ifndef GRPCXX_IMPL_CODEGEN_THRIFT_UTILS_H
#define GRPCXX_IMPL_CODEGEN_THRIFT_UTILS_H

#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/core_codegen_interface.h>
#include <grpc++/impl/codegen/serialization_traits.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/status_code_enum.h>
#include <grpc++/impl/codegen/thrift_serializer.h>
#include <grpc/impl/codegen/byte_buffer_reader.h>
#include <grpc/impl/codegen/slice.h>
#include <cstdint>
#include <cstdlib>

namespace grpc {

using apache::thrift::util::ThriftSerializerCompact;

template <class T>
class SerializationTraits<T, typename std::enable_if<std::is_base_of<
                                 apache::thrift::TBase, T>::value>::type> {
 public:
  static Status Serialize(const T& msg, grpc_byte_buffer** bp,
                          bool* own_buffer) {
    *own_buffer = true;

    ThriftSerializerCompact serializer;
    serializer.Serialize(msg, bp);

    return Status(StatusCode::OK, "ok");
  }

  static Status Deserialize(grpc_byte_buffer* buffer, T* msg,
                            int max_receive_message_size) {
    if (!buffer) {
      return Status(StatusCode::INTERNAL, "No payload");
    }

    ThriftSerializerCompact deserializer;
    deserializer.Deserialize(buffer, msg);

    grpc_byte_buffer_destroy(buffer);

    return Status(StatusCode::OK, "ok");
  }
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_THRIFT_UTILS_H
