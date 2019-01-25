
#ifndef GRPC_IMPL_CODEGEN_BYTE_BUFFER_READER_H
#define GRPC_IMPL_CODEGEN_BYTE_BUFFER_READER_H

#ifdef __cplusplus
extern "C" {
#endif

struct grpc_byte_buffer;

struct grpc_byte_buffer_reader {
  struct grpc_byte_buffer *buffer_in;
  struct grpc_byte_buffer *buffer_out;
  /* Different current objects correspond to different types of byte buffers */
  union {
    /* Index into a slice buffer's array of slices */
    unsigned index;
  } current;
};

#ifdef __cplusplus
}
#endif

#endif /* GRPC_IMPL_CODEGEN_BYTE_BUFFER_READER_H */
