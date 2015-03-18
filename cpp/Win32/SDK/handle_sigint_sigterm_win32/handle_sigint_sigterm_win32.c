/* 2015-03-18T16:14+08:00 */

/*
I wrote an example showing how to handle SIGINT, SIGTERM signals on CentOS
two months ago, and the source file can be found here:
https://github.com/myd7349/Ongoing-Study/blob/master/c/handle_sigint_sigterm.c

However, this example doesn't work on my Win7 x64 and at that time I didn't
know the Windows's way to do similar thing. Today, when I was learning CZMQ, 
the implementation code of function `zsys_handler_set` in `src/zsys.c` gives 
me the answer: via `SetConsoleCtrlHandler`.
*/
#ifndef USING_SetConsoleCtrlHandler
# define USING_SetConsoleCtrlHandler (1)
#endif

#include <windows.h>
#include <tchar.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>

#include "../../../../c/common.h"

static volatile BOOL g_bSheSayGoodbyeToMe = FALSE;

static void IHaveToWatchYouGoHelper(void)
{
    g_bSheSayGoodbyeToMe = TRUE;

    puts("\n--------------------------------------------------------");
    puts("I guess our love story will never be seen");
    puts("On the big wide silver screen");
    puts("But it hurt as bad");
    puts("When I had to watch you go");
    puts("--------------------------------------------------------");
}

#if USING_SetConsoleCtrlHandler
static BOOL WINAPI IHaveToWatchYouGo(DWORD dwWhySheLeavesMe)
{
    IHaveToWatchYouGoHelper();

    switch (dwWhySheLeavesMe) {
    case CTRL_C_EVENT:
        return TRUE;
    case CTRL_BREAK_EVENT:
        return TRUE;
    case CTRL_CLOSE_EVENT:
        return FALSE;
    case CTRL_LOGOFF_EVENT:
        return FALSE;
    case CTRL_SHUTDOWN_EVENT:
        return FALSE;
    default:
        assert(FALSE);
        return FALSE;
    }
}
#else
static void IHaveToWatchYouGo(int parm)
{
    (void)parm;

    IHaveToWatchYouGoHelper();
}
#endif

int main(void)
{
#if USING_SetConsoleCtrlHandler
    if (SetConsoleCtrlHandler(IHaveToWatchYouGo, TRUE)) {
        printf("She was once a true love of mine...");
        fflush(stdout);

        while (TRUE) {
            if (g_bSheSayGoodbyeToMe) {
                break;
            }
        }

        puts("The end of the world!");
    } else {
        puts("Never mind!");
    }
#else
    printf("She was once a true love of mine...");
    fflush(stdout);

    signal(SIGINT, IHaveToWatchYouGo);
    signal(SIGTERM, IHaveToWatchYouGo);

    while (TRUE) {
        if (g_bSheSayGoodbyeToMe) {
            break;
        }
    }

    puts("The end of the world!");
#endif

    PAUSE();
    return 0;
}

/*
References:
https://github.com/zeromq/czmq/blob/master/src/zsys.c
*/
