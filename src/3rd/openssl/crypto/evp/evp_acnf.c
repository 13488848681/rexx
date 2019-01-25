
#include "cryptlib.h"
#include <openssl/evp.h>
#include <openssl/conf.h>

/*
 * Load all algorithms and configure OpenSSL. This function is called
 * automatically when OPENSSL_LOAD_CONF is set.
 */

void OPENSSL_add_all_algorithms_conf(void)
{
    OPENSSL_add_all_algorithms_noconf();
    OPENSSL_config(NULL);
}
