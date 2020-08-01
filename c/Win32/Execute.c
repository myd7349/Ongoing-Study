#include "Execute.h"

#include <assert.h>

#include <shellapi.h>
#include <tchar.h>

#include "WindowsVersionHelpers.h"


// Functions shameless stolen from ProcessHacker:
// https://github.com/processhacker/processhacker/blob/3a601215d3964df52b111cc545af2bfc15dd00da/phlib/util.c#L2164
DWORD PhWaitForMultipleObjectsAndPump(
    __in_opt HWND hWnd,
    __in ULONG NumberOfHandles,
    __in PHANDLE Handles,
    __in ULONG Timeout
    )
{
    DWORD status;
    ULONG startTickCount;
    ULONG currentTickCount;
    LONG currentTimeout;

    startTickCount = GetTickCount();
    currentTimeout = Timeout;

    while (TRUE)
    {
        status = MsgWaitForMultipleObjects(
            NumberOfHandles,
            Handles,
            FALSE,
            (ULONG)currentTimeout,
            QS_ALLEVENTS
            );

        if (status >= STATUS_WAIT_0 && status < (DWORD)(STATUS_WAIT_0 + NumberOfHandles))
        {
            return status;
        }
        else if (status == (STATUS_WAIT_0 + NumberOfHandles))
        {
            MSG msg;

            // Pump messages

            while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            return status;
        }

        // Recompute the timeout value.

        if (Timeout != INFINITE)
        {
            currentTickCount = GetTickCount();
            currentTimeout = Timeout - (currentTickCount - startTickCount);

            if (currentTimeout < 0)
                return STATUS_TIMEOUT;
        }
    }
}


// Functions shameless stolen from ProcessHacker:
// https://github.com/processhacker/processhacker/blob/3a601215d3964df52b111cc545af2bfc15dd00da/phlib/util.c#L3165
// PhShellExecuteEx -> Execute
BOOL Execute(
    HWND hWnd,
    LPCTSTR lpcszFile,
    LPCTSTR lpcszArgs,
    INT nShowWindowType,
    DWORD dwExecuteFlags,
    DWORD dwTimeoutInMs,
    PHANDLE pHandle)
{
    SHELLEXECUTEINFO info = { sizeof(info) };

    assert(hWnd == NULL || IsWindow(hWnd));
    assert(lpcszFile != NULL);

    info.lpFile = lpcszFile;
    info.lpParameters = lpcszArgs;
    info.fMask = SEE_MASK_NOCLOSEPROCESS;
    info.nShow = nShowWindowType;
    info.hwnd = hWnd;

    if ((dwExecuteFlags & EXECUTE_ADMIN) && WINDOWS_HAS_UAC)
        info.lpVerb = _T("runas");

    if (ShellExecuteEx(&info))
    {
        if (dwTimeoutInMs)
        {
            if (!(dwExecuteFlags & EXECUTE_PUMP_MESSAGES))
            {
                WaitForSingleObject(info.hProcess, dwTimeoutInMs);
            }
            else
            {
                PhWaitForMultipleObjectsAndPump(NULL, 1, &info.hProcess, dwTimeoutInMs);
            }
        }

        if (pHandle)
            *pHandle = info.hProcess;
        else
            CloseHandle(info.hProcess);

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


// References:
// Ongoing-Study/cpp/Win32/MFC/Utility.h
// https://www.zhihu.com/question/37334646/answer/409253134
// TortoiseGit/src/Utils/CreateProcessHelper.h
// [AfxPumpMessage() is using for?](https://stackoverflow.com/questions/21304232/afxpumpmessage-is-using-for)
