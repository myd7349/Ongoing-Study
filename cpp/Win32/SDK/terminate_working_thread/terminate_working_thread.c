// 2015-03-12T08:25+08:00
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <process.h>
#include <tchar.h>
#include <windows.h>

static volatile BOOL g_bWorking;

static unsigned int __stdcall WorkingRoutine(void *arg)
{
    while (g_bWorking) {
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

    _ftprintf(stdout, _T("\nSee you, buddy!\n"));

    _tsystem(_T("pause"));
    return 0;
}