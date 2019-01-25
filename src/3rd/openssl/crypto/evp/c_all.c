
#include <stdio.h>
#include "cryptlib.h"
#include <openssl/evp.h>
#ifndef OPENSSL_NO_ENGINE
# include <openssl/engine.h>
#endif

#if 0
# undef OpenSSL_add_all_algorithms

void OpenSSL_add_all_algorithms(void)
{
    OPENSSL_add_all_algorithms_noconf();
}
#endif

void OPENSSL_add_all_algorithms_noconf(void)
{
    /*
     * For the moment OPENSSL_cpuid_setup does something
     * only on IA-32, but we reserve the option for all
     * platforms...
     */
    OPENSSL_cpuid_setup();
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();
}
