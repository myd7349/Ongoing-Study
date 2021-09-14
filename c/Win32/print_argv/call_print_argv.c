#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "Execute.h"


void Test(PCTSTR pszCommand, PCTSTR pcszArgs)
{
    ExecAppSync(pszCommand, pcszArgs, FALSE);
    _tsystem(_T("cmd /c type output.txt"));
    _putts(_T(""));
}


void RunProcess(PCTSTR pcszCommand, PCTSTR pcszArgs)
{
    BOOL bResult;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    PTSTR pszArgs = NULL;

    si.cb = sizeof(STARTUPINFO);
    ZeroMemory(&si, sizeof(si));

    ZeroMemory(&pi, sizeof(pi));

    pszArgs = _tcsdup(pcszArgs);

    bResult = CreateProcess(
        pcszCommand,
        pszArgs,
        NULL,
        NULL,
        TRUE,
        CREATE_NEW_CONSOLE, // If we pass 0 here, then this program will output nothing in Test2.
        NULL,
        NULL,
        &si,
        &pi);
    if (bResult)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        _tprintf(_T("CreateProcess failed: %u.\n"), GetLastError());
    }

    free(pszArgs);
}


void Test2(PCTSTR pszCommand, PCTSTR pcszArgs)
{
    RunProcess(pszCommand, pcszArgs);
    _tsystem(_T("cmd /c type output.txt"));
    _putts(_T(""));
}


int _tmain(void)
{
    Test(_T("print_argv.exe"), NULL);
    Test(_T("print_argv.exe"), _T("1 2 3"));
    Test(_T("print_argv.exe"), _T("print_argv.exe 1 2 3"));
    Test(_T("print_argv.exe"), _T("\"print_argv.exe\" 1 2 3"));
    Test(_T("print_argv.exe"), _T("\"print_argv.exe\" \"1\" \"2\" \"3\""));

    _putts(_T("----------------------------------------------------------------"));

    Test2(_T("print_argv.exe"), NULL);
    Test2(_T("print_argv.exe"), _T("1 2 3"));
    Test2(_T("print_argv.exe"), _T("print_argv.exe 1 2 3"));
    Test2(_T("print_argv.exe"), _T("\"print_argv.exe\" 1 2 3"));
    Test2(_T("print_argv.exe"), _T("\"print_argv.exe\" \"1\" \"2\" \"3\""));

    return 0;
}

// Question:
// If process A is created by process B via ShellExecuteEx, how can I pass all
// command line arguments to process B through process A?

// References:
// [What is the Windows equivalent of the Unix command cat?](https://superuser.com/questions/434870/what-is-the-windows-equivalent-of-the-unix-command-cat)
// [Why do we need to pass LPCTSTR lpParameters with ShellExecute](https://stackoverflow.com/questions/4313714/why-do-we-need-to-pass-lpctstr-lpparameters-with-shellexecute)
// [CreateProcess does not create additional console windows under Windows 7?](https://stackoverflow.com/questions/14958276/createprocess-does-not-create-additional-console-windows-under-windows-7)
// [GetCommandLine 分析](https://blog.csdn.net/jiangqin115/article/details/46660325)
// [GetCommandLine 分析](https://www.cnblogs.com/unicornsir/articles/10444635.html)
