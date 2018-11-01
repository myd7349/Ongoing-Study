// 2018-07-14T15:03+08:00
#include <stdio.h>

#include <conio.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


VOID CALLBACK TimerRoutine(
    __in  PVOID lpParameter,
    __in  BOOLEAN TimerOrWaitFired
    )
{
    static DWORD dwTickCount = 0;
    DWORD dwCurrent = GetTickCount();

    if (0 == dwTickCount)
        dwTickCount = (DWORD)lpParameter;

    _tprintf(_T("Thread [%05lu]> %lu ms elapsed.\n"),
        (unsigned long)GetCurrentThreadId(),
        (unsigned long)(dwCurrent - dwTickCount));
    dwTickCount = dwCurrent;

    Sleep(3000);

    _tprintf(_T("Thread [%05lu]> Goodbye!\n"),
        (unsigned long)GetCurrentThreadId());
}


int _tmain(int argc, _TCHAR **argv)
{
    HANDLE hTimerQueue = CreateTimerQueue();
    HANDLE hTimer = NULL;

    DWORD dwDueTimeInMs = 5000;
    DWORD dwPeriod = 1000;

    if (NULL == hTimerQueue)
    {
        _tperror(_T("Failed to create timer queue."));
        return GetLastError();
    }

    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
        TimerRoutine, (PVOID)GetTickCount(), dwDueTimeInMs, dwPeriod,
        WT_EXECUTEDEFAULT))
    {
        _tperror(_T("Failed to create timer."));
        return GetLastError();
    }

    _tprintf(_T("Call timer routine in %lu seconds...\n"),
        (unsigned long)dwDueTimeInMs / 1000);

    _tprintf(_T("Hit any key to delete the timer queue and cancel all queued timers!\n"));

    while (!_kbhit()) {
    }
    _getch();

    if (!DeleteTimerQueueEx(hTimerQueue, INVALID_HANDLE_VALUE))
    {
        _tprintf(_T("Failed to delete timer queue.\n"));
        return GetLastError();
    }

    _tprintf(_T("Now I think it is time to say goodbye.\n"));

    return 0;
}

// References:
// https://stackoverflow.com/questions/1435876/do-c-sharp-timers-elapse-on-a-separate-thread
// https://stackoverflow.com/questions/27115127/limits-of-windows-queue-timers
// https://www.codeproject.com/Articles/1236/Timers-Tutorial
// https://stackoverflow.com/questions/15381174/how-to-count-the-amount-of-concurrent-threads-in-net-application
// https://superuser.com/questions/347250/how-can-you-get-thread-count-of-running-process-in-windows-7
