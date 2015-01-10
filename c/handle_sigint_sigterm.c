/* 2015-01-10T12:53+08:00 */

/* 
 * A signal handling test inspired by an example in zguide:
 * https://github.com/imatix/zguide/blob/master/examples/C/interrupt.c
 * Background music: Bertie Higgins - Casablanca
 */

#include <signal.h>
#include <stdio.h>

static volatile sig_atomic_t she_say_goodbye_to_me = 0;

static void i_have_to_watch_you_go(int parm)
{
    (void)parm;

    she_say_goodbye_to_me = 1;

    puts("\n--------------------------------------------------------");
    puts("I guess our love story will never be seen");
    puts("On the big wide silver screen");
    puts("But it hurt as bad");
    puts("When I had to watch you go");
    puts("--------------------------------------------------------");
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = i_have_to_watch_you_go;
    action.sa_flags = 0;
    
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    printf("She was once a true love of mine...");
    fflush(stdout);
    while (1) {
        if (she_say_goodbye_to_me) {
            break;
        }
    }
    
    puts("The end of the world!");

    return 0;
}

/*
References:
signal函数、sigaction函数及信号集操作函数: http://blog.csdn.net/guoping16/article/details/6583957
*/
