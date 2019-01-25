
#ifndef GOOGLE_PROTOBUF_MACROS_H__
#define GOOGLE_PROTOBUF_MACROS_H__

#include <google/protobuf/stubs/port.h>

namespace google {
namespace protobuf {

#undef GOOGLE_DISALLOW_EVIL_CONSTRUCTORS
#define GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                           \
  void operator=(const TypeName&)

#undef GOOGLE_DISALLOW_IMPLICIT_CONSTRUCTORS
#define GOOGLE_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                           \
  TypeName(const TypeName&);                            \
  void operator=(const TypeName&)


#undef GOOGLE_ARRAYSIZE
#define GOOGLE_ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

// The COMPILE_ASSERT macro can be used to verify that a compile time
// expression is true. For example, you could use it to verify the
// size of a static array:
//
//   COMPILE_ASSERT(ARRAYSIZE(content_type_names) == CONTENT_NUM_TYPES,
//                  content_type_names_incorrect_size);
//
// or to make sure a struct is smaller than a certain size:
//
//   COMPILE_ASSERT(sizeof(foo) < 128, foo_too_large);
//
// The second argument to the macro is the name of the variable. If
// the expression is false, most compilers will issue a warning/error
// containing the name of the variable.

namespace internal {

template <bool>
struct CompileAssert {
};

}  // namespace internal

#undef GOOGLE_COMPILE_ASSERT
#if __cplusplus >= 201103L
#define GOOGLE_COMPILE_ASSERT(expr, msg) static_assert(expr, #msg)
#else
#define GOOGLE_COMPILE_ASSERT(expr, msg) \
  ::google::protobuf::internal::CompileAssert<(bool(expr))> \
          msg[bool(expr) ? 1 : -1]; \
  (void)msg

#endif  // __cplusplus >= 201103L

}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_MACROS_H__
