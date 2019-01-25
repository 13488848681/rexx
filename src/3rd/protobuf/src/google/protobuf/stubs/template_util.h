#ifndef GOOGLE_PROTOBUF_TEMPLATE_UTIL_H_
#define GOOGLE_PROTOBUF_TEMPLATE_UTIL_H_

namespace google {
namespace protobuf {
namespace internal {

// Types small_ and big_ are guaranteed such that sizeof(small_) <
// sizeof(big_)
typedef char small_;

struct big_ {
  char dummy[2];
};

// Identity metafunction.
template <class T>
struct identity_ {
  typedef T type;
};

// integral_constant, defined in tr1, is a wrapper for an integer
// value. We don't really need this generality; we could get away
// with hardcoding the integer type to bool. We use the fully
// general integer_constant for compatibility with tr1.

template<class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
};

template <class T, T v> const T integral_constant<T, v>::value;


// Abbreviations: true_type and false_type are structs that represent boolean
// true and false values. Also define the boost::mpl versions of those names,
// true_ and false_.
typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;
typedef true_type  true_;
typedef false_type false_;

// if_ is a templatized conditional statement.
// if_<cond, A, B> is a compile time evaluation of cond.
// if_<>::type contains A if cond is true, B otherwise.
template<bool cond, typename A, typename B>
struct if_{
  typedef A type;
};

template<typename A, typename B>
struct if_<false, A, B> {
  typedef B type;
};


// type_equals_ is a template type comparator, similar to Loki IsSameType.
// type_equals_<A, B>::value is true iff "A" is the same type as "B".
//
// New code should prefer base::is_same, defined in base/type_traits.h.
// It is functionally identical, but is_same is the standard spelling.
template<typename A, typename B>
struct type_equals_ : public false_ {
};

template<typename A>
struct type_equals_<A, A> : public true_ {
};

// and_ is a template && operator.
// and_<A, B>::value evaluates "A::value && B::value".
template<typename A, typename B>
struct and_ : public integral_constant<bool, (A::value && B::value)> {
};

// or_ is a template || operator.
// or_<A, B>::value evaluates "A::value || B::value".
template<typename A, typename B>
struct or_ : public integral_constant<bool, (A::value || B::value)> {
};


}  // namespace internal
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_TEMPLATE_UTIL_H_
