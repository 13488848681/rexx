
#include <stdio.h>
#include <openssl/err.h>
#include "rsaref_err.h"

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR
static ERR_STRING_DATA RSAREF_str_functs[] = {
    {ERR_PACK(0, RSAREF_F_BNREF_MOD_EXP, 0), "BNREF_MOD_EXP"},
    {ERR_PACK(0, RSAREF_F_CIPHER_DES_CBC_CODE, 0), "CIPHER_DES_CBC_CODE"},
    {ERR_PACK(0, RSAREF_F_RSAREF_BN2BIN, 0), "RSAREF_BN2BIN"},
    {ERR_PACK(0, RSAREF_F_RSAREF_MOD_EXP, 0), "RSAREF_MOD_EXP"},
    {ERR_PACK(0, RSAREF_F_RSAREF_PRIVATE_DECRYPT, 0),
     "RSAREF_PRIVATE_DECRYPT"},
    {ERR_PACK(0, RSAREF_F_RSAREF_PRIVATE_ENCRYPT, 0),
     "RSAREF_PRIVATE_ENCRYPT"},
    {ERR_PACK(0, RSAREF_F_RSAREF_PUBLIC_DECRYPT, 0), "RSAREF_PUBLIC_DECRYPT"},
    {ERR_PACK(0, RSAREF_F_RSAREF_PUBLIC_ENCRYPT, 0), "RSAREF_PUBLIC_ENCRYPT"},
    {ERR_PACK(0, RSAREF_F_RSA_BN2BIN, 0), "RSA_BN2BIN"},
    {ERR_PACK(0, RSAREF_F_RSA_PRIVATE_DECRYPT, 0), "RSA_PRIVATE_DECRYPT"},
    {ERR_PACK(0, RSAREF_F_RSA_PRIVATE_ENCRYPT, 0), "RSA_PRIVATE_ENCRYPT"},
    {ERR_PACK(0, RSAREF_F_RSA_PUBLIC_DECRYPT, 0), "RSA_PUBLIC_DECRYPT"},
    {ERR_PACK(0, RSAREF_F_RSA_PUBLIC_ENCRYPT, 0), "RSA_PUBLIC_ENCRYPT"},
    {0, NULL}
};

static ERR_STRING_DATA RSAREF_str_reasons[] = {
    {RSAREF_R_CONTENT_ENCODING, "content encoding"},
    {RSAREF_R_DATA, "data"},
    {RSAREF_R_DIGEST_ALGORITHM, "digest algorithm"},
    {RSAREF_R_ENCODING, "encoding"},
    {RSAREF_R_ENCRYPTION_ALGORITHM, "encryption algorithm"},
    {RSAREF_R_KEY, "key"},
    {RSAREF_R_KEY_ENCODING, "key encoding"},
    {RSAREF_R_LEN, "len"},
    {RSAREF_R_LENGTH_NOT_BLOCK_ALIGNED, "length not block aligned"},
    {RSAREF_R_MODULUS_LEN, "modulus len"},
    {RSAREF_R_NEED_RANDOM, "need random"},
    {RSAREF_R_PRIVATE_KEY, "private key"},
    {RSAREF_R_PUBLIC_KEY, "public key"},
    {RSAREF_R_SIGNATURE, "signature"},
    {RSAREF_R_SIGNATURE_ENCODING, "signature encoding"},
    {RSAREF_R_UNKNOWN_FAULT, "unknown fault"},
    {0, NULL}
};

#endif

#ifdef RSAREF_LIB_NAME
static ERR_STRING_DATA RSAREF_lib_name[] = {
    {0, RSAREF_LIB_NAME},
    {0, NULL}
};
#endif

static int RSAREF_lib_error_code = 0;
static int RSAREF_error_init = 1;

static void ERR_load_RSAREF_strings(void)
{
    if (RSAREF_lib_error_code == 0)
        RSAREF_lib_error_code = ERR_get_next_error_library();

    if (RSAREF_error_init) {
        RSAREF_error_init = 0;
#ifndef OPENSSL_NO_ERR
        ERR_load_strings(RSAREF_lib_error_code, RSAREF_str_functs);
        ERR_load_strings(RSAREF_lib_error_code, RSAREF_str_reasons);
#endif

#ifdef RSAREF_LIB_NAME
        RSAREF_lib_name->error = ERR_PACK(RSAREF_lib_error_code, 0, 0);
        ERR_load_strings(0, RSAREF_lib_name);
#endif
    }
}

static void ERR_unload_RSAREF_strings(void)
{
    if (RSAREF_error_init == 0) {
#ifndef OPENSSL_NO_ERR
        ERR_unload_strings(RSAREF_lib_error_code, RSAREF_str_functs);
        ERR_unload_strings(RSAREF_lib_error_code, RSAREF_str_reasons);
#endif

#ifdef RSAREF_LIB_NAME
        ERR_unload_strings(0, RSAREF_lib_name);
#endif
        RSAREF_error_init = 1;
    }
}

static void ERR_RSAREF_error(int function, int reason, char *file, int line)
{
    if (RSAREF_lib_error_code == 0)
        RSAREF_lib_error_code = ERR_get_next_error_library();
    ERR_PUT_error(RSAREF_lib_error_code, function, reason, file, line);
}
