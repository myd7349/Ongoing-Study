// 2018-08-06T12:17+08:00
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <process.h>
#include <tchar.h>
#include <windows.h>


#define NUMBER_OF_HANDLES (0)

#define UM_SPEED_UP       (WM_APP + 1)
#define UM_SLOW_DOWN      (WM_APP + 2)
#define UM_RESET          (WM_APP + 3)
#define UM_QUIT           WM_QUIT

#define INTERVAL_DEFAULT  (200)
#define INTERVAL_MAX      (5000)
#define INTERVAL_MIN      (5)


static unsigned int __stdcall WorkingRoutine(void *arg)
{
    DWORD dwResult;
    DWORD dwMs = INTERVAL_DEFAULT;

    MSG msg;
    // We need a message queue.
    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

    while ((dwResult = MsgWaitForMultipleObjectsEx(
        NUMBER_OF_HANDLES, NULL, 0, QS_ALLEVENTS, MWMO_ALERTABLE)) != WAIT_FAILED)
    {
        if (dwResult >= STATUS_WAIT_0 && dwResult < STATUS_WAIT_0 + NUMBER_OF_HANDLES)
        {
            _tprintf(_T("[%u] Handles are signaled.\n"), (unsigned)GetCurrentThreadId());
        }
        else if (dwResult == STATUS_WAIT_0 + NUMBER_OF_HANDLES)
        {
            msg.message = 0;
            PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

            _tprintf(_T("[%u] Received message %u.\n"), (unsigned)GetCurrentThreadId(), (unsigned)msg.message);

            if (msg.message == UM_QUIT)
                break;

            switch (msg.message)
            {
            case UM_SPEED_UP:
                dwMs = max(dwMs / 2, INTERVAL_MIN);
                _tprintf(_T("[%u] Current interval is %ums.\n"), (unsigned)GetCurrentThreadId(), (unsigned)dwMs);
                break;
            case UM_SLOW_DOWN:
                dwMs = min(dwMs * 2, INTERVAL_MAX);
                _tprintf(_T("[%u] Current interval is %ums.\n"), (unsigned)GetCurrentThreadId(), (unsigned)dwMs);
                break;
            case UM_RESET:
                dwMs = INTERVAL_DEFAULT;
                _tprintf(_T("[%u] Current interval is %ums.\n"), (unsigned)GetCurrentThreadId(), (unsigned)dwMs);
                break;
            default:
                assert(0);
                break;
            }
        }
        else if (dwResult == WAIT_TIMEOUT)
        {
            _puttc(_T('.'), stdout);
            Sleep(dwMs);
        }
        else
        {
            assert(0);
            _tprintf(_T("[%u] No Way!!!\n"), (unsigned)GetCurrentThreadId());
        }
    }

    return 0;
}


int _tmain(int argc, _TCHAR **argv)
{
    int ch;
    unsigned int uThreadId;
    HANDLE hWorkingThread = (HANDLE)_beginthreadex(
        NULL,
        0,
        WorkingRoutine,
        NULL,
        CREATE_SUSPENDED,
        &uThreadId);

    if (NULL == hWorkingThread)
    {
        _ftprintf(stderr, _T("Creating working thread failed!\n"));
        return EXIT_FAILURE;
    }

    ResumeThread(hWorkingThread);

    SetConsoleTitle(_T("Q/Esc: Quit    >/+: Speed up    </-: Slow down    R: Reset"));

    while (1)
    {
        while (!_kbhit())
        {
        }

        ch = tolower(_getch());
        if (ch == 'q' || ch == 27) // esc
            break;
        else if (ch == 'r')
            PostThreadMessage((DWORD)uThreadId, UM_RESET, 0, 0);
        else if (ch == 46 || ch == 61) // > +
            PostThreadMessage((DWORD)uThreadId, UM_SPEED_UP, 0, 0);
        else if (ch == 44 || ch == 45) // < -
            PostThreadMessage((DWORD)uThreadId, UM_SLOW_DOWN, 0, 0);
    }

    PostThreadMessage((DWORD)uThreadId, UM_QUIT, 0, 0);
    WaitForSingleObject(hWorkingThread, INFINITE);
    CloseHandle(hWorkingThread);

    _ftprintf(stdout, _T("\nSee you, buddy!\n"));

    _tsystem(_T("pause"));
    return 0;
}

// References:
// [Multi-threaded Client/Server Socket Class](https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class)
// Ongoing-Study/c/Win32/Execute.c
// Multithreading Applications in Win32, Chapter 05
