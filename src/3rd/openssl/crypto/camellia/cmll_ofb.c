
#include <openssl/camellia.h>
#include <openssl/modes.h>

/*
 * The input and output encrypted as though 128bit ofb mode is being used.
 * The extra state information to record how much of the 128bit block we have
 * used is contained in *num;
 */
void Camellia_ofb128_encrypt(const unsigned char *in, unsigned char *out,
                             size_t length, const CAMELLIA_KEY *key,
                             unsigned char *ivec, int *num)
{
    CRYPTO_ofb128_encrypt(in, out, length, key, ivec, num,
                          (block128_f) Camellia_encrypt);
}
