

/* the location of <hash_map> */
#define GOOGLE_PROTOBUF_HASH_MAP_H <hash_map>


// TODO(kenton):  Use unordered_map instead, which is available in MSVC 2010.
#if _MSC_VER < 1310 || _MSC_VER >= 1600
#define GOOGLE_PROTOBUF_HASH_NAMESPACE std
#else
#define GOOGLE_PROTOBUF_HASH_NAMESPACE stdext
#endif

/* the location of <hash_set> */
#define GOOGLE_PROTOBUF_HASH_SET_H <hash_set>

/* define if the compiler has hash_map */
#define GOOGLE_PROTOBUF_HAVE_HASH_MAP 1

/* define if the compiler has hash_set */
#define GOOGLE_PROTOBUF_HAVE_HASH_SET 1

/* define if you want to use zlib.  See readme.txt for additional
 * requirements. */
// #define HAVE_ZLIB 1
