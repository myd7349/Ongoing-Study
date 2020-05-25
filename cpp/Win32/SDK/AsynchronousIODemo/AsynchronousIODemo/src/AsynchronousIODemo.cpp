// 2018-08-01T18:14+08:00
#include <stdio.h>

#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../../../../../common.h"


int _tmain(int argc, _TCHAR *argv[])
{
    if (argc != 2)
    {
        _ftprintf(stderr, _T("Usage: %s <file>\n"), GetProgName(argv[0]).c_str());
        return 0;
    }

    HANDLE hFile = CreateFile(
        argv[1],
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE)
    {
        _ftprintf(stderr, _T("Failed to open file \"%s\"!\n"), argv[1]);
        return EXIT_FAILURE;
    }
    
    OVERLAPPED overlapped = { 0 };

    return 0;
}

// HasOverlappedIoCompleted

// References:
// Multithreading Applications in Win32, Ch06
