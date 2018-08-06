// 2018-08-06T12:17+08:00
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <process.h>
#include <tchar.h>
#include <windows.h>


#define NUMBER_OF_HANDLES (0)


static unsigned int __stdcall WorkingRoutine(void *arg)
{
    DWORD dwResult;

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

            if (msg.message == WM_QUIT)
                break;
        }
        else if (dwResult == WAIT_TIMEOUT)
        {
            _puttc(_T('.'), stdout);
            Sleep(200);
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

    SetConsoleTitle(_T("Hit any key to terminate the working thread!"));

    while (!_kbhit())
    {
    }
    _getch();

    PostThreadMessage((DWORD)uThreadId, WM_QUIT, 0, 0);
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
