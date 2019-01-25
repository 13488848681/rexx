
#ifndef _SHA256_H_
#define _SHA256_H_

#include <sys/types.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct libscrypt_SHA256Context {
	uint32_t state[8];
	uint32_t count[2];
	unsigned char buf[64];
} SHA256_CTX;

typedef struct libscrypt_HMAC_SHA256Context {
	SHA256_CTX ictx;
	SHA256_CTX octx;
} HMAC_SHA256_CTX;

void	libscrypt_SHA256_Init(/*@out@*/ SHA256_CTX *);
void	libscrypt_SHA256_Update(SHA256_CTX *, const void *, size_t);

/* Original declaration: 
 *	void    SHA256_Final(unsigned char [32], SHA256_CTX *);
*/
void	libscrypt_SHA256_Final(/*@out@*/ unsigned char [], SHA256_CTX *);
void	libscrypt_HMAC_SHA256_Init(HMAC_SHA256_CTX *, const void *, size_t);
void	libscrypt_HMAC_SHA256_Update(HMAC_SHA256_CTX *, const void *, size_t);

/* Original declaration:
 *	void    HMAC_SHA256_Final(unsigned char [32], HMAC_SHA256_CTX *);
*/
void	libscrypt_HMAC_SHA256_Final(unsigned char [], HMAC_SHA256_CTX *);

/**
 * PBKDF2_SHA256(passwd, passwdlen, salt, saltlen, c, buf, dkLen):
 * Compute PBKDF2(passwd, salt, c, dkLen) using HMAC-SHA256 as the PRF, and
 * write the output to buf.  The value dkLen must be at most 32 * (2^32 - 1).
 */
void	libscrypt_PBKDF2_SHA256(const uint8_t *, size_t, const uint8_t *, size_t,
    uint64_t, uint8_t *, size_t);

#ifdef __cplusplus
}
#endif

#endif /* !_SHA256_H_ */
