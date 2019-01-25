
#include <openssl/e_os2.h>

#ifdef OPENSSL_BUILD_SHLIBCRYPTO
# undef OPENSSL_EXTERN
# define OPENSSL_EXTERN OPENSSL_EXPORT
#endif

/* The following macros make sure the names are different from libdes names */
#define DES_version OSSL_DES_version
#define libdes_version OSSL_libdes_version

/* SSLeay version string */
OPENSSL_EXTERN const char OSSL_DES_version[];
/* old libdes version string */
OPENSSL_EXTERN const char OSSL_libdes_version[];
