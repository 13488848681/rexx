
#ifndef GRPCXX_IMPL_CODEGEN_COMPLETION_QUEUE_TAG_H
#define GRPCXX_IMPL_CODEGEN_COMPLETION_QUEUE_TAG_H

namespace grpc {

/// An interface allowing implementors to process and filter event tags.
class CompletionQueueTag {
 public:
  virtual ~CompletionQueueTag() {}
  // Called prior to returning from Next(), return value is the status of the
  // operation (return status is the default thing to do). If this function
  // returns false, the tag is dropped and not returned from the completion
  // queue
  virtual bool FinalizeResult(void** tag, bool* status) = 0;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_COMPLETION_QUEUE_TAG_H
