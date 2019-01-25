
#include <stdio.h>
#include "cryptlib.h"
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

void PEM_SignInit(EVP_MD_CTX *ctx, EVP_MD *type)
{
    EVP_DigestInit_ex(ctx, type, NULL);
}

void PEM_SignUpdate(EVP_MD_CTX *ctx, unsigned char *data, unsigned int count)
{
    EVP_DigestUpdate(ctx, data, count);
}

int PEM_SignFinal(EVP_MD_CTX *ctx, unsigned char *sigret,
                  unsigned int *siglen, EVP_PKEY *pkey)
{
    unsigned char *m;
    int i, ret = 0;
    unsigned int m_len;

    m = (unsigned char *)OPENSSL_malloc(EVP_PKEY_size(pkey) + 2);
    if (m == NULL) {
        PEMerr(PEM_F_PEM_SIGNFINAL, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_SignFinal(ctx, m, &m_len, pkey) <= 0)
        goto err;

    i = EVP_EncodeBlock(sigret, m, m_len);
    *siglen = i;
    ret = 1;
 err:
    /* ctx has been zeroed by EVP_SignFinal() */
    if (m != NULL)
        OPENSSL_free(m);
    return (ret);
}
