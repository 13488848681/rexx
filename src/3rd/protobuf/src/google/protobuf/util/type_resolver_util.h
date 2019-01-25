
#ifndef GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_UTIL_H__
#define GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_UTIL_H__

#include <string>

#include <google/protobuf/stubs/common.h>
namespace google {
namespace protobuf {
class DescriptorPool;
namespace util {
class TypeResolver;

// Creates a TypeResolver that serves type information in the given descriptor
// pool. Caller takes ownership of the returned TypeResolver.
LIBPROTOBUF_EXPORT TypeResolver* NewTypeResolverForDescriptorPool(
    const string& url_prefix, const DescriptorPool* pool);

}  // namespace util
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_UTIL_TYPE_RESOLVER_UTIL_H__
