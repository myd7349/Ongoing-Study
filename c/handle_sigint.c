/* 2015-01-09T16:30+08:00  */

/* Signal handling and non-local jump test on CentOS. */

#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*sig_handler)(int);

sigjmp_buf env_buf;

void sigint_handler(int parm)
{
    siglongjmp(env_buf, 1);
}

int main(void)
{
    sig_handler prev_handler = signal(SIGINT, sigint_handler);
    if (SIG_ERR == prev_handler) {
        fputs("Failed to register SIGINT handler\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sigsetjmp(env_buf, 1)) {
        puts("We have a lot of work to do in our whole life...");
        while (1);
    } else {
        puts("Now, just take a rest and enjoy this journey!");
    }

    return EXIT_SUCCESS;    
}
