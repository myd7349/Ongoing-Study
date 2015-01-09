/* 2015-01-09T16:30+08:00  */

/* Signal handling and non-local jump test on CentOS. */

/* On Win7 x64, if I replace sigjmp_buf, sigsetjmp, siglongjmp with jmp_buf, setjmp, longjmp, 
 * then this program just crashes.
 */

#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*sig_handler)(int);

static sigjmp_buf env_buf;

static void sigint_handler(int parm)
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

/*
References:
24.4.3 Nonlocal Control Transfer in Handlers: http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Longjmp-in-Handler.html
CS360 Lecture notes -- Setjmp: http://web.eecs.utk.edu/~huangj/cs360/360/notes/Setjmp/lecture.html
Exception Handling Differences: http://msdn.microsoft.com/en-us/library/de5awhsw.aspx
Exceptions in C with Longjmp and Setjmp: http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
Is it good programming practice to use setjmp and longjmp in C?: http://stackoverflow.com/questions/7262494/is-it-good-programming-practice-to-use-setjmp-and-longjmp-in-c
longjmp() from signal handler: http://stackoverflow.com/questions/1715413/longjmp-from-signal-handler
Mixing C (Structured) and C++ Exceptions: http://msdn.microsoft.com/en-us/library/5skw957f.aspx
Using setjmp/longjmp: http://msdn.microsoft.com/en-us/library/yz2ez4as.aspx
*/
