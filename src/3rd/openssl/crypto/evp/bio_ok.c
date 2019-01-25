
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "cryptlib.h"
#include <openssl/buffer.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

static int ok_write(BIO *h, const char *buf, int num);
static int ok_read(BIO *h, char *buf, int size);
static long ok_ctrl(BIO *h, int cmd, long arg1, void *arg2);
static int ok_new(BIO *h);
static int ok_free(BIO *data);
static long ok_callback_ctrl(BIO *h, int cmd, bio_info_cb *fp);

static int sig_out(BIO *b);
static int sig_in(BIO *b);
static int block_out(BIO *b);
static int block_in(BIO *b);
#define OK_BLOCK_SIZE   (1024*4)
#define OK_BLOCK_BLOCK  4
#define IOBS            (OK_BLOCK_SIZE+ OK_BLOCK_BLOCK+ 3*EVP_MAX_MD_SIZE)
#define WELLKNOWN "The quick brown fox jumped over the lazy dog's back."

typedef struct ok_struct {
    size_t buf_len;
    size_t buf_off;
    size_t buf_len_save;
    size_t buf_off_save;
    int cont;                   /* <= 0 when finished */
    int finished;
    EVP_MD_CTX md;
    int blockout;               /* output block is ready */
    int sigio;                  /* must process signature */
    unsigned char buf[IOBS];
} BIO_OK_CTX;

static BIO_METHOD methods_ok = {
    BIO_TYPE_CIPHER, "reliable",
    ok_write,
    ok_read,
    NULL,                       /* ok_puts, */
    NULL,                       /* ok_gets, */
    ok_ctrl,
    ok_new,
    ok_free,
    ok_callback_ctrl,
};

BIO_METHOD *BIO_f_reliable(void)
{
    return (&methods_ok);
}

static int ok_new(BIO *bi)
{
    BIO_OK_CTX *ctx;

    ctx = (BIO_OK_CTX *)OPENSSL_malloc(sizeof(BIO_OK_CTX));
    if (ctx == NULL)
        return (0);

    ctx->buf_len = 0;
    ctx->buf_off = 0;
    ctx->buf_len_save = 0;
    ctx->buf_off_save = 0;
    ctx->cont = 1;
    ctx->finished = 0;
    ctx->blockout = 0;
    ctx->sigio = 1;

    EVP_MD_CTX_init(&ctx->md);

    bi->init = 0;
    bi->ptr = (char *)ctx;
    bi->flags = 0;
    return (1);
}

static int ok_free(BIO *a)
{
    if (a == NULL)
        return (0);
    EVP_MD_CTX_cleanup(&((BIO_OK_CTX *)a->ptr)->md);
    OPENSSL_cleanse(a->ptr, sizeof(BIO_OK_CTX));
    OPENSSL_free(a->ptr);
    a->ptr = NULL;
    a->init = 0;
    a->flags = 0;
    return (1);
}

static int ok_read(BIO *b, char *out, int outl)
{
    int ret = 0, i, n;
    BIO_OK_CTX *ctx;

    if (out == NULL)
        return (0);
    ctx = (BIO_OK_CTX *)b->ptr;

    if ((ctx == NULL) || (b->next_bio == NULL) || (b->init == 0))
        return (0);

    while (outl > 0) {

        /* copy clean bytes to output buffer */
        if (ctx->blockout) {
            i = ctx->buf_len - ctx->buf_off;
            if (i > outl)
                i = outl;
            memcpy(out, &(ctx->buf[ctx->buf_off]), i);
            ret += i;
            out += i;
            outl -= i;
            ctx->buf_off += i;

            /* all clean bytes are out */
            if (ctx->buf_len == ctx->buf_off) {
                ctx->buf_off = 0;

                /*
                 * copy start of the next block into proper place
                 */
                if (ctx->buf_len_save - ctx->buf_off_save > 0) {
                    ctx->buf_len = ctx->buf_len_save - ctx->buf_off_save;
                    memmove(ctx->buf, &(ctx->buf[ctx->buf_off_save]),
                            ctx->buf_len);
                } else {
                    ctx->buf_len = 0;
                }
                ctx->blockout = 0;
            }
        }

        /* output buffer full -- cancel */
        if (outl == 0)
            break;

        /* no clean bytes in buffer -- fill it */
        n = IOBS - ctx->buf_len;
        i = BIO_read(b->next_bio, &(ctx->buf[ctx->buf_len]), n);

        if (i <= 0)
            break;              /* nothing new */

        ctx->buf_len += i;

        /* no signature yet -- check if we got one */
        if (ctx->sigio == 1) {
            if (!sig_in(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }

        /* signature ok -- check if we got block */
        if (ctx->sigio == 0) {
            if (!block_in(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }

        /* invalid block -- cancel */
        if (ctx->cont <= 0)
            break;

    }

    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return (ret);
}

static int ok_write(BIO *b, const char *in, int inl)
{
    int ret = 0, n, i;
    BIO_OK_CTX *ctx;

    if (inl <= 0)
        return inl;

    ctx = (BIO_OK_CTX *)b->ptr;
    ret = inl;

    if ((ctx == NULL) || (b->next_bio == NULL) || (b->init == 0))
        return (0);

    if (ctx->sigio && !sig_out(b))
        return 0;

    do {
        BIO_clear_retry_flags(b);
        n = ctx->buf_len - ctx->buf_off;
        while (ctx->blockout && n > 0) {
            i = BIO_write(b->next_bio, &(ctx->buf[ctx->buf_off]), n);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                if (!BIO_should_retry(b))
                    ctx->cont = 0;
                return (i);
            }
            ctx->buf_off += i;
            n -= i;
        }

        /* at this point all pending data has been written */
        ctx->blockout = 0;
        if (ctx->buf_len == ctx->buf_off) {
            ctx->buf_len = OK_BLOCK_BLOCK;
            ctx->buf_off = 0;
        }

        if ((in == NULL) || (inl <= 0))
            return (0);

        n = (inl + ctx->buf_len > OK_BLOCK_SIZE + OK_BLOCK_BLOCK) ?
            (int)(OK_BLOCK_SIZE + OK_BLOCK_BLOCK - ctx->buf_len) : inl;

        memcpy((unsigned char *)(&(ctx->buf[ctx->buf_len])),
               (unsigned char *)in, n);
        ctx->buf_len += n;
        inl -= n;
        in += n;

        if (ctx->buf_len >= OK_BLOCK_SIZE + OK_BLOCK_BLOCK) {
            if (!block_out(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }
    } while (inl > 0);

    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return (ret);
}

static long ok_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    BIO_OK_CTX *ctx;
    EVP_MD *md;
    const EVP_MD **ppmd;
    long ret = 1;
    int i;

    ctx = b->ptr;

    switch (cmd) {
    case BIO_CTRL_RESET:
        ctx->buf_len = 0;
        ctx->buf_off = 0;
        ctx->buf_len_save = 0;
        ctx->buf_off_save = 0;
        ctx->cont = 1;
        ctx->finished = 0;
        ctx->blockout = 0;
        ctx->sigio = 1;
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        break;
    case BIO_CTRL_EOF:         /* More to read */
        if (ctx->cont <= 0)
            ret = 1;
        else
            ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        break;
    case BIO_CTRL_PENDING:     /* More to read in buffer */
    case BIO_CTRL_WPENDING:    /* More to read in buffer */
        ret = ctx->blockout ? ctx->buf_len - ctx->buf_off : 0;
        if (ret <= 0)
            ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        break;
    case BIO_CTRL_FLUSH:
        /* do a final write */
        if (ctx->blockout == 0)
            if (!block_out(b))
                return 0;

        while (ctx->blockout) {
            i = ok_write(b, NULL, 0);
            if (i < 0) {
                ret = i;
                break;
            }
        }

        ctx->finished = 1;
        ctx->buf_off = ctx->buf_len = 0;
        ctx->cont = (int)ret;

        /* Finally flush the underlying BIO */
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        break;
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;
    case BIO_CTRL_INFO:
        ret = (long)ctx->cont;
        break;
    case BIO_C_SET_MD:
        md = ptr;
        if (!EVP_DigestInit_ex(&ctx->md, md, NULL))
            return 0;
        b->init = 1;
        break;
    case BIO_C_GET_MD:
        if (b->init) {
            ppmd = ptr;
            *ppmd = ctx->md.digest;
        } else
            ret = 0;
        break;
    default:
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        break;
    }
    return (ret);
}

static long ok_callback_ctrl(BIO *b, int cmd, bio_info_cb *fp)
{
    long ret = 1;

    if (b->next_bio == NULL)
        return (0);
    switch (cmd) {
    default:
        ret = BIO_callback_ctrl(b->next_bio, cmd, fp);
        break;
    }
    return (ret);
}

static void longswap(void *_ptr, size_t len)
{
    const union {
        long one;
        char little;
    } is_endian = {
        1
    };

    if (is_endian.little) {
        size_t i;
        unsigned char *p = _ptr, c;

        for (i = 0; i < len; i += 4) {
            c = p[0], p[0] = p[3], p[3] = c;
            c = p[1], p[1] = p[2], p[2] = c;
        }
    }
}

static int sig_out(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;

    ctx = b->ptr;
    md = &ctx->md;

    if (ctx->buf_len + 2 * md->digest->md_size > OK_BLOCK_SIZE)
        return 1;

    if (!EVP_DigestInit_ex(md, md->digest, NULL))
        goto berr;
    /*
     * FIXME: there's absolutely no guarantee this makes any sense at all,
     * particularly now EVP_MD_CTX has been restructured.
     */
    if (RAND_bytes(md->md_data, md->digest->md_size) <= 0)
        goto berr;
    memcpy(&(ctx->buf[ctx->buf_len]), md->md_data, md->digest->md_size);
    longswap(&(ctx->buf[ctx->buf_len]), md->digest->md_size);
    ctx->buf_len += md->digest->md_size;

    if (!EVP_DigestUpdate(md, WELLKNOWN, strlen(WELLKNOWN)))
        goto berr;
    if (!EVP_DigestFinal_ex(md, &(ctx->buf[ctx->buf_len]), NULL))
        goto berr;
    ctx->buf_len += md->digest->md_size;
    ctx->blockout = 1;
    ctx->sigio = 0;
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}

static int sig_in(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned char tmp[EVP_MAX_MD_SIZE];
    int ret = 0;

    ctx = b->ptr;
    md = &ctx->md;

    if ((int)(ctx->buf_len - ctx->buf_off) < 2 * md->digest->md_size)
        return 1;

    if (!EVP_DigestInit_ex(md, md->digest, NULL))
        goto berr;
    memcpy(md->md_data, &(ctx->buf[ctx->buf_off]), md->digest->md_size);
    longswap(md->md_data, md->digest->md_size);
    ctx->buf_off += md->digest->md_size;

    if (!EVP_DigestUpdate(md, WELLKNOWN, strlen(WELLKNOWN)))
        goto berr;
    if (!EVP_DigestFinal_ex(md, tmp, NULL))
        goto berr;
    ret = memcmp(&(ctx->buf[ctx->buf_off]), tmp, md->digest->md_size) == 0;
    ctx->buf_off += md->digest->md_size;
    if (ret == 1) {
        ctx->sigio = 0;
        if (ctx->buf_len != ctx->buf_off) {
            memmove(ctx->buf, &(ctx->buf[ctx->buf_off]),
                    ctx->buf_len - ctx->buf_off);
        }
        ctx->buf_len -= ctx->buf_off;
        ctx->buf_off = 0;
    } else {
        ctx->cont = 0;
    }
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}

static int block_out(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned long tl;

    ctx = b->ptr;
    md = &ctx->md;

    tl = ctx->buf_len - OK_BLOCK_BLOCK;
    ctx->buf[0] = (unsigned char)(tl >> 24);
    ctx->buf[1] = (unsigned char)(tl >> 16);
    ctx->buf[2] = (unsigned char)(tl >> 8);
    ctx->buf[3] = (unsigned char)(tl);
    if (!EVP_DigestUpdate(md,
                          (unsigned char *)&(ctx->buf[OK_BLOCK_BLOCK]), tl))
        goto berr;
    if (!EVP_DigestFinal_ex(md, &(ctx->buf[ctx->buf_len]), NULL))
        goto berr;
    ctx->buf_len += md->digest->md_size;
    ctx->blockout = 1;
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}

static int block_in(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned long tl = 0;
    unsigned char tmp[EVP_MAX_MD_SIZE];

    ctx = b->ptr;
    md = &ctx->md;

    assert(sizeof(tl) >= OK_BLOCK_BLOCK); /* always true */
    tl = ctx->buf[0];
    tl <<= 8;
    tl |= ctx->buf[1];
    tl <<= 8;
    tl |= ctx->buf[2];
    tl <<= 8;
    tl |= ctx->buf[3];

    if (ctx->buf_len < tl + OK_BLOCK_BLOCK + md->digest->md_size)
        return 1;

    if (!EVP_DigestUpdate(md,
                          (unsigned char *)&(ctx->buf[OK_BLOCK_BLOCK]), tl))
        goto berr;
    if (!EVP_DigestFinal_ex(md, tmp, NULL))
        goto berr;
    if (memcmp(&(ctx->buf[tl + OK_BLOCK_BLOCK]), tmp, md->digest->md_size) ==
        0) {
        /* there might be parts from next block lurking around ! */
        ctx->buf_off_save = tl + OK_BLOCK_BLOCK + md->digest->md_size;
        ctx->buf_len_save = ctx->buf_len;
        ctx->buf_off = OK_BLOCK_BLOCK;
        ctx->buf_len = tl + OK_BLOCK_BLOCK;
        ctx->blockout = 1;
    } else {
        ctx->cont = 0;
    }
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}
