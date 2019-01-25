
#ifndef GRPCXX_IMPL_CODEGEN_TIME_H
#define GRPCXX_IMPL_CODEGEN_TIME_H

#include <grpc++/impl/codegen/config.h>
#include <grpc/impl/codegen/grpc_types.h>

namespace grpc {

/* If you are trying to use CompletionQueue::AsyncNext with a time class that
   isn't either gpr_timespec or std::chrono::system_clock::time_point, you
   will most likely be looking at this comment as your compiler will have
   fired an error below. In order to fix this issue, you have two potential
   solutions:

     1. Use gpr_timespec or std::chrono::system_clock::time_point instead
     2. Specialize the TimePoint class with whichever time class that you
        want to use here. See below for two examples of how to do this.
 */

template <typename T>
class TimePoint {
 public:
  TimePoint(const T& time) { you_need_a_specialization_of_TimePoint(); }
  gpr_timespec raw_time() {
    gpr_timespec t;
    return t;
  }

 private:
  void you_need_a_specialization_of_TimePoint();
};

template <>
class TimePoint<gpr_timespec> {
 public:
  TimePoint(const gpr_timespec& time) : time_(time) {}
  gpr_timespec raw_time() { return time_; }

 private:
  gpr_timespec time_;
};

}  // namespace grpc

#include <chrono>

#include <grpc/impl/codegen/grpc_types.h>

namespace grpc {

// from and to should be absolute time.
void Timepoint2Timespec(const std::chrono::system_clock::time_point& from,
                        gpr_timespec* to);
void TimepointHR2Timespec(
    const std::chrono::high_resolution_clock::time_point& from,
    gpr_timespec* to);

std::chrono::system_clock::time_point Timespec2Timepoint(gpr_timespec t);

template <>
class TimePoint<std::chrono::system_clock::time_point> {
 public:
  TimePoint(const std::chrono::system_clock::time_point& time) {
    Timepoint2Timespec(time, &time_);
  }
  gpr_timespec raw_time() const { return time_; }

 private:
  gpr_timespec time_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_TIME_H
