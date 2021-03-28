// 2015-03-12T08:25+08:00
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <process.h>
#include <tchar.h>
#include <windows.h>

static __declspec(align(8)) volatile LONG g_bWorking;

static unsigned int __stdcall WorkingRoutine(void *arg)
{
    while (InterlockedCompareExchange(&g_bWorking, 0, 0)) {
        _puttc(_T('.'), stdout);
        Sleep(200);
    }

    return 0;
}

int _tmain(int argc, _TCHAR **argv)
{
    HANDLE hWorkingThread = (HANDLE)_beginthreadex(
        NULL, 
        0, 
        WorkingRoutine,
        NULL,
        CREATE_SUSPENDED,
        NULL);

    if (NULL == hWorkingThread) {
        _ftprintf(stderr, _T("Creating working thread failed!\n"));
        return EXIT_FAILURE;
    }

    g_bWorking = TRUE;
    ResumeThread(hWorkingThread);

    SetConsoleTitle(_T("Hit any key to terminate the working thread!"));

    while (!_kbhit()) {
    }
    _getch();

    InterlockedExchange(&g_bWorking, FALSE);
    WaitForSingleObject(hWorkingThread, INFINITE);
    CloseHandle(hWorkingThread);

    _ftprintf(stdout, _T("\nSee you, buddy!\n"));

    _tsystem(_T("pause"));
    return 0;
}

/*
References:
[Can I call CloseHandle() immediately after _beginthreadex() succeeded?](http://stackoverflow.com/questions/8241712/can-i-call-closehandle-immediately-after-beginthreadex-succeeded)
https://www.zhihu.com/question/31490495
[谈谈 C/C++ 中的 volatile](https://zhuanlan.zhihu.com/p/33074506) - [谈谈 C/C++ 中的 volatile](https://liam.page/2018/01/18/volatile-in-C-and-Cpp/)
[When to use volatile with multi threading?](https://stackoverflow.com/questions/4557979/when-to-use-volatile-with-multi-threading)
https://github.com/Liam0205/liam0205.github.io/tree/master/2020/10/14/implement-a-timed-looper-in-cxx
[Reading interlocked variables](https://stackoverflow.com/questions/779996/reading-interlocked-variables)
[Atomic load in C with MSVC](https://stackoverflow.com/questions/42660091/atomic-load-in-c-with-msvc)
https://stackoverflow.com/questions/3855671/how-do-i-atomically-swap-2-ints-in-c/3855824#3855824
https://stackoverflow.com/questions/4285666/interlocked-ops-vs-xxxatomic-on-win32
*/
