
#include <stddef.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>

/* Old netscape certificate wrapper format */

ASN1_SEQUENCE(NETSCAPE_X509) = {
        ASN1_SIMPLE(NETSCAPE_X509, header, ASN1_OCTET_STRING),
        ASN1_OPT(NETSCAPE_X509, cert, X509)
} ASN1_SEQUENCE_END(NETSCAPE_X509)

IMPLEMENT_ASN1_FUNCTIONS(NETSCAPE_X509)
