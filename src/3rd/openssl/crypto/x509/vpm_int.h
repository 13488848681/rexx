
struct X509_VERIFY_PARAM_ID_st {
    STACK_OF(OPENSSL_STRING) *hosts; /* Set of acceptable names */
    unsigned int hostflags;     /* Flags to control matching features */
    char *peername;             /* Matching hostname in peer certificate */
    char *email;                /* If not NULL email address to match */
    size_t emaillen;
    unsigned char *ip;          /* If not NULL IP address to match */
    size_t iplen;               /* Length of IP address */
};
