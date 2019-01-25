
#include "cryptlib.h"
#include <openssl/rand.h>
#include "rand_lcl.h"

#if defined (OPENSSL_SYS_NETWARE)

# if defined(NETWARE_LIBC)
#  include <nks/thread.h>
# else
#  include <nwthread.h>
# endif

extern int GetProcessSwitchCount(void);
# if !defined(NETWARE_LIBC) || (CURRENT_NDK_THRESHOLD < 509220000)
extern void *RunningProcess;    /* declare here same as found in newer NDKs */
extern unsigned long GetSuperHighResolutionTimer(void);
# endif

   /*
    * the FAQ indicates we need to provide at least 20 bytes (160 bits) of
    * seed
    */
int RAND_poll(void)
{
    unsigned long l;
    unsigned long tsc;
    int i;

    /*
     * There are several options to gather miscellaneous data but for now we
     * will loop checking the time stamp counter (rdtsc) and the
     * SuperHighResolutionTimer.  Each iteration will collect 8 bytes of data
     * but it is treated as only 1 byte of entropy.  The call to
     * ThreadSwitchWithDelay() will introduce additional variability into the
     * data returned by rdtsc. Applications can agument the seed material by
     * adding additional stuff with RAND_add() and should probably do so.
     */
    l = GetProcessSwitchCount();
    RAND_add(&l, sizeof(l), 1);

    /* need to cast the void* to unsigned long here */
    l = (unsigned long)RunningProcess;
    RAND_add(&l, sizeof(l), 1);

    for (i = 2; i < ENTROPY_NEEDED; i++) {
# ifdef __MWERKS__
        asm {
        rdtsc mov tsc, eax}
# elif defined(__GNUC__) && __GNUC__>=2 && !defined(OPENSSL_NO_ASM) && !defined(OPENSSL_NO_INLINE_ASM)
        asm volatile ("rdtsc":"=a" (tsc)::"edx");
# endif

        RAND_add(&tsc, sizeof(tsc), 1);

        l = GetSuperHighResolutionTimer();
        RAND_add(&l, sizeof(l), 0);

# if defined(NETWARE_LIBC)
        NXThreadYield();
# else                          /* NETWARE_CLIB */
        ThreadSwitchWithDelay();
# endif
    }

    return 1;
}

#endif
