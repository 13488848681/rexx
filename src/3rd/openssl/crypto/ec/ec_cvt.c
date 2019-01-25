
#include <openssl/err.h>
#include "ec_lcl.h"

#ifdef OPENSSL_FIPS
# include <openssl/fips.h>
#endif

EC_GROUP *EC_GROUP_new_curve_GFp(const BIGNUM *p, const BIGNUM *a,
                                 const BIGNUM *b, BN_CTX *ctx)
{
    const EC_METHOD *meth;
    EC_GROUP *ret;

#ifdef OPENSSL_FIPS
    if (FIPS_mode())
        return FIPS_ec_group_new_curve_gfp(p, a, b, ctx);
#endif
#if defined(OPENSSL_BN_ASM_MONT)
    /*
     * This might appear controversial, but the fact is that generic
     * prime method was observed to deliver better performance even
     * for NIST primes on a range of platforms, e.g.: 60%-15%
     * improvement on IA-64, ~25% on ARM, 30%-90% on P4, 20%-25%
     * in 32-bit build and 35%--12% in 64-bit build on Core2...
     * Coefficients are relative to optimized bn_nist.c for most
     * intensive ECDSA verify and ECDH operations for 192- and 521-
     * bit keys respectively. Choice of these boundary values is
     * arguable, because the dependency of improvement coefficient
     * from key length is not a "monotone" curve. For example while
     * 571-bit result is 23% on ARM, 384-bit one is -1%. But it's
     * generally faster, sometimes "respectfully" faster, sometimes
     * "tolerably" slower... What effectively happens is that loop
     * with bn_mul_add_words is put against bn_mul_mont, and the
     * latter "wins" on short vectors. Correct solution should be
     * implementing dedicated NxN multiplication subroutines for
     * small N. But till it materializes, let's stick to generic
     * prime method...
     *                                              <appro>
     */
    meth = EC_GFp_mont_method();
#else
    meth = EC_GFp_nist_method();
#endif

    ret = EC_GROUP_new(meth);
    if (ret == NULL)
        return NULL;

    if (!EC_GROUP_set_curve_GFp(ret, p, a, b, ctx)) {
        unsigned long err;

        err = ERR_peek_last_error();

        if (!(ERR_GET_LIB(err) == ERR_LIB_EC &&
              ((ERR_GET_REASON(err) == EC_R_NOT_A_NIST_PRIME) ||
               (ERR_GET_REASON(err) == EC_R_NOT_A_SUPPORTED_NIST_PRIME)))) {
            /* real error */

            EC_GROUP_clear_free(ret);
            return NULL;
        }

        /*
         * not an actual error, we just cannot use EC_GFp_nist_method
         */

        ERR_clear_error();

        EC_GROUP_clear_free(ret);
        meth = EC_GFp_mont_method();

        ret = EC_GROUP_new(meth);
        if (ret == NULL)
            return NULL;

        if (!EC_GROUP_set_curve_GFp(ret, p, a, b, ctx)) {
            EC_GROUP_clear_free(ret);
            return NULL;
        }
    }

    return ret;
}

#ifndef OPENSSL_NO_EC2M
EC_GROUP *EC_GROUP_new_curve_GF2m(const BIGNUM *p, const BIGNUM *a,
                                  const BIGNUM *b, BN_CTX *ctx)
{
    const EC_METHOD *meth;
    EC_GROUP *ret;

# ifdef OPENSSL_FIPS
    if (FIPS_mode())
        return FIPS_ec_group_new_curve_gf2m(p, a, b, ctx);
# endif
    meth = EC_GF2m_simple_method();

    ret = EC_GROUP_new(meth);
    if (ret == NULL)
        return NULL;

    if (!EC_GROUP_set_curve_GF2m(ret, p, a, b, ctx)) {
        EC_GROUP_clear_free(ret);
        return NULL;
    }

    return ret;
}
#endif
