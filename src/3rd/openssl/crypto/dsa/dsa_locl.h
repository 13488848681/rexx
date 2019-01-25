
#include <openssl/dsa.h>

int dsa_builtin_paramgen(DSA *ret, size_t bits, size_t qbits,
                         const EVP_MD *evpmd, const unsigned char *seed_in,
                         size_t seed_len, unsigned char *seed_out,
                         int *counter_ret, unsigned long *h_ret,
                         BN_GENCB *cb);

int dsa_builtin_paramgen2(DSA *ret, size_t L, size_t N,
                          const EVP_MD *evpmd, const unsigned char *seed_in,
                          size_t seed_len, int idx, unsigned char *seed_out,
                          int *counter_ret, unsigned long *h_ret,
                          BN_GENCB *cb);

int dsa_paramgen_check_g(DSA *dsa);
