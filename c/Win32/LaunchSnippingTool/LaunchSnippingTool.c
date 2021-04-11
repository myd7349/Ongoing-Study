#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

#include "Execute.h"
#include "WindowsVersionHelpers.h"


int _tmain(void)
{
#if 0
    // TODO: It returns False on my Win10.
    if (!IsWindows10OrGreater())
    {
        MessageBox(
            NULL,
            _T("Please run this application on Win10."),
            _T(""),
            MB_OK | MB_ICONWARNING);

        return 0;
    }
#endif

    LPCTSTR lpcszSnippingToolPath = _T("C:\\Windows\\System32\\SnippingTool.exe");
    MessageBox(
        NULL,
        lpcszSnippingToolPath,
        _T("SnippingTool path:"),
        MB_OK | MB_ICONINFORMATION);

#if _WIN64
    MessageBox(NULL, _T("This application is built with a 64-bit compiler."), _T(""), MB_OK | MB_ICONINFORMATION);
#else
    MessageBox(NULL, _T("This application is built with a 32-bit compiler."), _T(""), MB_OK | MB_ICONINFORMATION);
#endif

#if _WIN64
    ExecAppSync(lpcszSnippingToolPath, NULL, FALSE);
#else
    int iResponse = MessageBox(
        NULL,
        _T("You are running an 32-bit application on a x64 PC.\nDo you want to disable file system redirector?"),
        _T(""),
        MB_YESNO | MB_ICONQUESTION
    );
    if (iResponse == IDYES)
    {
        PVOID pOldValue = NULL;
        if (Wow64DisableWow64FsRedirection(&pOldValue)) 
        {
            ExecAppSync(lpcszSnippingToolPath, NULL, FALSE);

            if (!Wow64RevertWow64FsRedirection(pOldValue))
                return 1;
        }
    }
    else
    {
        ExecAppSync(lpcszSnippingToolPath, NULL, FALSE);
    }
#endif

    return 0;
}


// References:
// [Determining 32 vs 64 bit in C++](https://stackoverflow.com/questions/1505582/determining-32-vs-64-bit-in-c)
// [Can not launch SnippingTool (elevation is required)](https://github.com/pywinauto/pywinauto/issues/890)
/*
The reason:
You Win10 is 64-bit, and your Python app might be 32-bit.
When you typied `C:\WINDOWS\system32\SnippingTool.exe`, the file system redirector will redirects it to `C:\WINDOWS\SysWOW64\SnippingTool.exe`.

To resolve this issue, we may use either of the three ways:
1. Run the python script with a 64-bit Python;
2. Disable file system redirector;
3. Call `SHGetKnownFolderPath` instead of specify `C:\Windows\System32`;

References:
* [File System Redirector](https://docs.microsoft.com/en-us/windows/win32/winprog64/file-system-redirector)
* [Wow64DisableWow64FsRedirection](https://docs.microsoft.com/en-us/windows/win32/api/wow64apiset/nf-wow64apiset-wow64disablewow64fsredirection)
* [Launch SnippingTool.exe from c++ program](http://www.cplusplus.com/forum/general/79335/)
*/
