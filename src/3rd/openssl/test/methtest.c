
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include "meth.h"
#include <openssl/err.h>

int main(argc, argv)
int argc;
char *argv[];
{
    METHOD_CTX *top, *tmp1, *tmp2;

    top = METH_new(x509_lookup()); /* get a top level context */
    if (top == NULL)
        goto err;

    tmp1 = METH_new(x509_by_file());
    if (top == NULL)
        goto err;
    METH_arg(tmp1, METH_TYPE_FILE, "cafile1");
    METH_arg(tmp1, METH_TYPE_FILE, "cafile2");
    METH_push(top, METH_X509_CA_BY_SUBJECT, tmp1);

    tmp2 = METH_new(x509_by_dir());
    METH_arg(tmp2, METH_TYPE_DIR, "/home/eay/.CAcerts");
    METH_arg(tmp2, METH_TYPE_DIR, "/home/eay/SSLeay/certs");
    METH_arg(tmp2, METH_TYPE_DIR, "/usr/local/ssl/certs");
    METH_push(top, METH_X509_CA_BY_SUBJECT, tmp2);

/*- tmp=METH_new(x509_by_issuer_dir);
    METH_arg(tmp,METH_TYPE_DIR,"/home/eay/.mycerts");
    METH_push(top,METH_X509_BY_ISSUER,tmp);

    tmp=METH_new(x509_by_issuer_primary);
    METH_arg(tmp,METH_TYPE_FILE,"/home/eay/.mycerts/primary.pem");
    METH_push(top,METH_X509_BY_ISSUER,tmp);
*/

    METH_init(top);
    METH_control(tmp1, METH_CONTROL_DUMP, stdout);
    METH_control(tmp2, METH_CONTROL_DUMP, stdout);
    EXIT(0);
 err:
    ERR_load_crypto_strings();
    ERR_print_errors_fp(stderr);
    EXIT(1);
    return (0);
}
