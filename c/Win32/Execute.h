#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#ifdef __cplusplus
extern "C"
{
#endif


#define EXECUTE_ADMIN         0x1
#define EXECUTE_PUMP_MESSAGES 0x2

BOOL Execute(
    HWND hWnd,
    LPCTSTR lpcszFile,
    LPCTSTR lpcszArgs,
    INT nShowWindowType,
    DWORD dwExecuteFlags,
    DWORD dwTimeoutInMs,
    PHANDLE pHandle);

#define ExecDaemonSync(lpcszFile, lpcszArgs, bRunAsAdmin)  Execute(NULL, (lpcszFile), (lpcszArgs), SW_HIDE, (bRunAsAdmin ? EXECUTE_ADMIN : 0), INFINITE, NULL)
#define ExecDaemonAsync(lpcszFile, lpcszArgs, bRunAsAdmin) Execute(NULL, (lpcszFile), (lpcszArgs), SW_HIDE, (bRunAsAdmin ? EXECUTE_ADMIN : 0), 0, NULL)
#define ExecAppSync(lpcszFile, lpcszArgs, bRunAsAdmin)     Execute(NULL, (lpcszFile), (lpcszArgs), SW_SHOW, (bRunAsAdmin ? EXECUTE_ADMIN : 0), INFINITE, NULL)
#define ExecAppAsync(lpcszFile, lpcszArgs, bRunAsAdmin)    Execute(NULL, (lpcszFile), (lpcszArgs), SW_SHOW, (bRunAsAdmin ? EXECUTE_ADMIN : 0), 0, NULL)

#ifdef __cplusplus
}
#endif
