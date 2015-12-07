// 2015-11-11T14:49+08:00
#include "stdafx.h"
#include "MagnifierAPI.h"


void OpenMagnifier(LPCTSTR lpcszAppPath)
{
    TCHAR szCmdLine[1024];
    lstrcpyn(szCmdLine, lpcszAppPath, _countof(szCmdLine));

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = SW_SHOWNORMAL;

    PROCESS_INFORMATION pi = { NULL };

    if (CreateProcess(NULL, szCmdLine, NULL, NULL, 
        FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        ::CloseHandle(pi.hThread);
        ::CloseHandle(pi.hProcess);
    }
}

BOOL IsMagnifierOpened()
{
    HWND hWndMag = FindWindow(_T("MagnifierByMYD"), _T("放大镜"));
    return hWndMag != NULL;
}

void CloseMagnifier()
{
    HWND hWndMag = FindWindow(_T("MagnifierByMYD"), _T("放大镜"));
    if (hWndMag != NULL && IsWindow(hWndMag))
    {
        SendMessage(hWndMag, WM_CLOSE, 0, 0);
    }
}