// 2018-08-01T18:25+08:00
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <process.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


static HANDLE gs_hRequestExitEvent = FALSE;

static int gs_nDots;
static int gs_nStars;


static void ExpensiveSleep(DWORD dwMs)
{
    DWORD dwStartMs = GetTickCount();

    if (dwMs == 0)
        return;

    while (GetTickCount() - dwStartMs < dwMs)
    {
    }
}


static unsigned int __stdcall WorkingRoutine(void *arg)
{
    TCHAR ch = (TCHAR)(INT_PTR)arg;
    int *pCounter = ch == _T('.') ? &gs_nDots : &gs_nStars;

    assert(gs_hRequestExitEvent != NULL);

    while (1)
    {
        if (WaitForSingleObject(gs_hRequestExitEvent, 0) != WAIT_TIMEOUT)
            return 1;

        (*pCounter)++;
        _puttc(ch, stdout);
        ExpensiveSleep(200);
    }

    return 0;
}


int _tmain(int argc, _TCHAR **argv)
{
    HANDLE hWorkingThreads[2] = { NULL, NULL };
    TCHAR  chChars[2] = { _T('.'), _T('*') };
    int    nPriorities[2] = { THREAD_PRIORITY_TIME_CRITICAL, THREAD_PRIORITY_IDLE };
    size_t i;

    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    for (i = 0; i < ARRAYSIZE(hWorkingThreads); ++i)
    {
        hWorkingThreads[i] = (HANDLE)_beginthreadex(
            NULL, 0, WorkingRoutine, (void *)(INT_PTR)chChars[i],
            CREATE_SUSPENDED, NULL);

        if (NULL == hWorkingThreads[i])
        {
            _ftprintf(stderr, _T("Creating working thread failed!\n"));
            return EXIT_FAILURE;
        }

        SetThreadPriority(hWorkingThreads[i], nPriorities[i]);
    }

    gs_hRequestExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (NULL == gs_hRequestExitEvent)
    {
        _ftprintf(stderr, _T("Creating event failed!\n"));
        return EXIT_FAILURE;
    }

    for (i = 0; i < ARRAYSIZE(hWorkingThreads); ++i)
        ResumeThread(hWorkingThreads[i]);

    SetConsoleTitle(_T("Hit any key to terminate the working thread!"));

    while (!_kbhit())
    {
    }
    _getch();
    SetEvent(gs_hRequestExitEvent);

    WaitForMultipleObjects(ARRAYSIZE(hWorkingThreads), hWorkingThreads, TRUE, INFINITE);
    for (i = 0; i < ARRAYSIZE(hWorkingThreads); ++i)
        CloseHandle(hWorkingThreads[i]);

    CloseHandle(gs_hRequestExitEvent);

    _ftprintf(stdout, _T("\nSee you, buddy!\n"));
    _ftprintf(stdout, _T("Stars: %d, Dots: %d\n"), gs_nStars, gs_nDots);

    _tsystem(_T("pause"));
    return 0;
}

// References:
// Multithreading Applications in Win32, P106
