#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

#include "high_timer.h"


void missed_alarm(int signum)
{
    /* we missed a timer signal, so won't be sending packets fast enough!!! */
    write(2, "Missed Alarm!\n", 14); /* can't use printf in a signal handler */
}


int main(void)
{
    struct itimerval timer;
    sigset_t alarm_sig;
    int signum;

    int counter = 0;
    high_timer_t high_timer;

    signal(SIGALRM, missed_alarm);

    timer.it_interval.tv_sec = timer.it_value.tv_sec = 0;
    timer.it_interval.tv_usec = timer.it_value.tv_usec = 1000; /* 1000 microseconds */

    if (setitimer(ITIMER_REAL, &timer, 0) < 0)
    {
        perror("setitimer");
        return EXIT_FAILURE;
    }

    sigemptyset(&alarm_sig);
    sigaddset(&alarm_sig, SIGALRM);

    while (1)
    {
        if (counter == 0)
            high_timer_start(&high_timer);

        sigwait(&alarm_sig, &signum); /* wait until the next signal */

        if (++counter == 1000)
        {
            counter = 0;
            printf("Elapsed microseconds: %"PRId64"\n",
                high_timer_elapsed_us(&high_timer));
        }
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/25327519/how-to-send-udp-packet-every-1-ms
// https://www.freebsd.org/cgi/man.cgi?query=setitimer&sektion=2&apropos=0&manpath=FreeBSD+6.2-RELEASE
// https://linux.die.net/man/2/setitimer
// https://github.com/slideinc/itimer/blob/master/itimermodule.c
// https://github.com/slideinc/itimer
// https://www.teuniz.net/Timer_code/index.html
