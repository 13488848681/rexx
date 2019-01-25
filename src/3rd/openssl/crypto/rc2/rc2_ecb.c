
#include <openssl/rc2.h>
#include "rc2_locl.h"
#include <openssl/opensslv.h>

const char RC2_version[] = "RC2" OPENSSL_VERSION_PTEXT;

/*-
 * RC2 as implemented frm a posting from
 * Newsgroups: sci.crypt
 * Sender: pgut01@cs.auckland.ac.nz (Peter Gutmann)
 * Subject: Specification for Ron Rivests Cipher No.2
 * Message-ID: <4fk39f$f70@net.auckland.ac.nz>
 * Date: 11 Feb 1996 06:45:03 GMT
 */

void RC2_ecb_encrypt(const unsigned char *in, unsigned char *out, RC2_KEY *ks,
                     int encrypt)
{
    unsigned long l, d[2];

    c2l(in, l);
    d[0] = l;
    c2l(in, l);
    d[1] = l;
    if (encrypt)
        RC2_encrypt(d, ks);
    else
        RC2_decrypt(d, ks);
    l = d[0];
    l2c(l, out);
    l = d[1];
    l2c(l, out);
    l = d[0] = d[1] = 0;
}
