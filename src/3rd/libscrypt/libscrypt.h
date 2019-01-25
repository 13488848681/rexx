/*-
 */
#ifndef _CRYPTO_SCRYPT_H_
#define _CRYPTO_SCRYPT_H_

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

int libscrypt_scrypt(const uint8_t *, size_t, const uint8_t *, size_t, uint64_t,
    uint32_t, uint32_t, /*@out@*/ uint8_t *, size_t);

/* Converts a series of input parameters to a MCF form for storage */
int libscrypt_mcf(uint32_t N, uint32_t r, uint32_t p, const char *salt,
	const char *hash, char *mcf);

/* Checks a given MCF against a password */
int libscrypt_check(char *mcf, const char *password);

#ifdef __cplusplus
}
#endif

/* Sane default values */
#define SCRYPT_HASH_LEN 64 /* This can be user defined - 
 *but 64 is the reference size
 */
#define SCRYPT_SAFE_N 30 /* This is much higher than you want. It's just
			  * a blocker for insane defines
			  */
#define SCRYPT_SALT_LEN 16 /* This is just a recommended size */
#define SCRYPT_MCF_LEN 125 /* mcf is 120 byte + nul */
#define SCRYPT_MCF_ID "$s1"
#define SCRYPT_N 16384
#define SCRYPT_r 8
#define SCRYPT_p 16
#endif /* !_CRYPTO_SCRYPT_H_ */
