
#include <stdio.h>
#include <openssl/objects.h>
#include "ssl_locl.h"

static const SSL_METHOD *dtls1_get_method(int ver);
static const SSL_METHOD *dtls1_get_method(int ver)
{
    if (ver == DTLS_ANY_VERSION)
        return DTLS_method();
    else if (ver == DTLS1_VERSION)
        return DTLSv1_method();
    else if (ver == DTLS1_2_VERSION)
        return DTLSv1_2_method();
    else
        return NULL;
}

IMPLEMENT_dtls1_meth_func(DTLS1_VERSION,
                          DTLSv1_method,
                          dtls1_accept,
                          dtls1_connect, dtls1_get_method, DTLSv1_enc_data)

IMPLEMENT_dtls1_meth_func(DTLS1_2_VERSION,
                          DTLSv1_2_method,
                          dtls1_accept,
                          dtls1_connect, dtls1_get_method, DTLSv1_2_enc_data)

IMPLEMENT_dtls1_meth_func(DTLS_ANY_VERSION,
                          DTLS_method,
                          dtls1_accept,
                          dtls1_connect, dtls1_get_method, DTLSv1_2_enc_data)
