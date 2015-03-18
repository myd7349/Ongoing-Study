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

#include <windows.h>
#include <tchar.h>

#include <assert.h>
#include <stdio.h>

#include "../../../../c/common.h"

static volatile BOOL g_bSheSayGoodbyeToMe = FALSE;

static BOOL WINAPI IHaveToWatchYouGo(DWORD dwWhySheLeavesMe)
{
    g_bSheSayGoodbyeToMe = TRUE;
    
    _putts(_T("\n--------------------------------------------------------"));
    _putts(_T("I guess our love story will never be seen"));
    _putts(_T("On the big wide silver screen"));
    _putts(_T("But it hurt as bad"));
    _putts(_T("When I had to watch you go"));
    _putts(_T("--------------------------------------------------------"));

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

int _tmain(void)
{
    if (SetConsoleCtrlHandler(IHaveToWatchYouGo, TRUE)) {
        _tprintf(_T("She was once a true love of mine..."));
        fflush(stdout);

        while (TRUE) {
            if (g_bSheSayGoodbyeToMe) {
                break;
            }
        }

        _putts(_T("The end of the world!"));
    } else {
        _putts(_T("Never mind!"));
    }

    PAUSE();
    return 0;
}

/*
References:
https://github.com/zeromq/czmq/blob/master/src/zsys.c
*/
