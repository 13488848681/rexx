
#include <stdlib.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


#define TOTAL_NUM_TESTS                         2
#define TEST_SSL_CTX                            0

#define SSLV2ON                                 1
#define SSLV2OFF                                0

SSL_CONF_CTX *confctx;
SSL_CTX *ctx;
SSL *ssl;

static int checksslv2(int test, int sslv2)
{
    int options;
    if (test == TEST_SSL_CTX) {
        options = SSL_CTX_get_options(ctx);
    } else {
        options = SSL_get_options(ssl);
    }
    return ((options & SSL_OP_NO_SSLv2) == 0) ^ (sslv2 == SSLV2OFF);
}

int main(int argc, char *argv[])
{
    BIO *err;
    int testresult = 0;
    int currtest = 0;

    SSL_library_init();
    SSL_load_error_strings();

    err = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);

    CRYPTO_malloc_debug_init();
    CRYPTO_set_mem_debug_options(V_CRYPTO_MDEBUG_ALL);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);


    confctx = SSL_CONF_CTX_new();
    ctx = SSL_CTX_new(SSLv23_method());
    ssl = SSL_new(ctx);
    if (confctx == NULL || ctx == NULL)
        goto end;

    SSL_CONF_CTX_set_flags(confctx, SSL_CONF_FLAG_FILE
                                    | SSL_CONF_FLAG_CLIENT
                                    | SSL_CONF_FLAG_SERVER);

    /*
     * For each test set up an SSL_CTX and SSL and see whether SSLv2 is enabled
     * as expected after various SSL_CONF_cmd("Protocol", ...) calls.
     */
    for (currtest = 0; currtest < TOTAL_NUM_TESTS; currtest++) {
        BIO_printf(err, "SSLv2 CONF Test number %d\n", currtest);
        if (currtest == TEST_SSL_CTX)
            SSL_CONF_CTX_set_ssl_ctx(confctx, ctx);
        else
            SSL_CONF_CTX_set_ssl(confctx, ssl);

        /* SSLv2 should be off by default */
        if (!checksslv2(currtest, SSLV2OFF)) {
            BIO_printf(err, "SSLv2 CONF Test: Off by default test FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "ALL") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");
            goto end;
        }

        /* Should still be off even after ALL Protocols on */
        if (!checksslv2(currtest, SSLV2OFF)) {
            BIO_printf(err, "SSLv2 CONF Test: Off after config #1 FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "SSLv2") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");
            goto end;
        }

        /* Should still be off even if explicitly asked for */
        if (!checksslv2(currtest, SSLV2OFF)) {
            BIO_printf(err, "SSLv2 CONF Test: Off after config #2 FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "-SSLv2") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");;
            goto end;
        }

        if (!checksslv2(currtest, SSLV2OFF)) {
            BIO_printf(err, "SSLv2 CONF Test: Off after config #3 FAIL\n");
            goto end;
        }

        if (currtest == TEST_SSL_CTX)
            SSL_CTX_clear_options(ctx, SSL_OP_NO_SSLv2);
        else
            SSL_clear_options(ssl, SSL_OP_NO_SSLv2);

        if (!checksslv2(currtest, SSLV2ON)) {
            BIO_printf(err, "SSLv2 CONF Test: On after clear FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "ALL") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");
            goto end;
        }

        /* Option has been cleared and config says have SSLv2 so should be on */
        if (!checksslv2(currtest, SSLV2ON)) {
            BIO_printf(err, "SSLv2 CONF Test: On after config #1 FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "SSLv2") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");
            goto end;
        }

        /* Option has been cleared and config says have SSLv2 so should be on */
        if (!checksslv2(currtest, SSLV2ON)) {
            BIO_printf(err, "SSLv2 CONF Test: On after config #2 FAIL\n");
            goto end;
        }

        if (SSL_CONF_cmd(confctx, "Protocol", "-SSLv2") != 2
                || !SSL_CONF_CTX_finish(confctx)) {
            BIO_printf(err, "SSLv2 CONF Test: SSL_CONF command FAIL\n");
            goto end;
        }

        /* Option has been cleared but config says no SSLv2 so should be off */
        if (!checksslv2(currtest, SSLV2OFF)) {
            BIO_printf(err, "SSLv2 CONF Test: Off after config #4 FAIL\n");
            goto end;
        }

    }

    testresult = 1;

 end:
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    SSL_CONF_CTX_free(confctx);

    if (!testresult) {
        printf("SSLv2 CONF test: FAILED (Test %d)\n", currtest);
        ERR_print_errors(err);
    } else {
        printf("SSLv2 CONF test: PASSED\n");
    }

    ERR_free_strings();
    ERR_remove_thread_state(NULL);
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    CRYPTO_mem_leaks(err);
    BIO_free(err);

    return testresult ? EXIT_SUCCESS : EXIT_FAILURE;
}
