
#ifndef GRPCXX_ALARM_H
#define GRPCXX_ALARM_H

#include <grpc++/impl/codegen/completion_queue.h>
#include <grpc++/impl/codegen/completion_queue_tag.h>
#include <grpc++/impl/codegen/grpc_library.h>
#include <grpc++/impl/codegen/time.h>
#include <grpc++/impl/grpc_library.h>
#include <grpc/grpc.h>

struct grpc_alarm;

namespace grpc {

class CompletionQueue;

/// A thin wrapper around \a grpc_alarm (see / \a / src/core/surface/alarm.h).
class Alarm : private GrpcLibraryCodegen {
 public:
  template <typename T>
  Alarm(CompletionQueue* cq, const T& deadline, void* tag)
      : tag_(tag),
        alarm_(grpc_alarm_create(cq->cq(), TimePoint<T>(deadline).raw_time(),
                                 static_cast<void*>(&tag_))) {}

  /// Destroy the given completion queue alarm, cancelling it in the process.
  ~Alarm() { grpc_alarm_destroy(alarm_); }

  /// Cancel a completion queue alarm. Calling this function over an alarm that
  /// has already fired has no effect.
  void Cancel() { grpc_alarm_cancel(alarm_); }

 private:
  class AlarmEntry : public CompletionQueueTag {
   public:
    AlarmEntry(void* tag) : tag_(tag) {}
    bool FinalizeResult(void** tag, bool* status) override {
      *tag = tag_;
      return true;
    }

   private:
    void* tag_;
  };

  AlarmEntry tag_;
  grpc_alarm* const alarm_;  // owned
};

}  // namespace grpc

#endif  // GRPCXX_ALARM_H
