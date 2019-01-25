#ifndef HEADER_OPENSSLV_H
# define HEADER_OPENSSLV_H

#ifdef  __cplusplus
extern "C" {
#endif


# define OPENSSL_VERSION_NUMBER  0x100020afL
# ifdef OPENSSL_FIPS
#  define OPENSSL_VERSION_TEXT    "OpenSSL 1.0.2j-fips  26 Sep 2016"
# else
#  define OPENSSL_VERSION_TEXT    "OpenSSL 1.0.2j  26 Sep 2016"
# endif
# define OPENSSL_VERSION_PTEXT   " part of " OPENSSL_VERSION_TEXT


# define SHLIB_VERSION_HISTORY ""
# define SHLIB_VERSION_NUMBER "1.0.0"


#ifdef  __cplusplus
}
#endif
#endif                          /* HEADER_OPENSSLV_H */
