#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


void SetEnvironmentVariableX(PCTSTR pszName, PCTSTR pszValue)
{
    TCHAR szBuffer[100] = _T("");
    DWORD dwResult;
    BOOL bResult = SetEnvironmentVariable(pszName, pszValue);

    if (bResult)
    {
        dwResult = GetEnvironmentVariable(pszName, szBuffer, ARRAYSIZE(szBuffer));
        if (dwResult != 0)
            _tprintf(_T("GetEnvironmentVariable(%s): %s.\n"), pszName, szBuffer);
        else
            _tprintf(_T("GetEnvironmentVariable(%s) failed(%u).\n"), pszName, dwResult);
    }
    else
    {
        _tprintf(_T("SetEnvironmentVariable(%s) failed(%u).\n"), pszName, GetLastError());
    }
}


void PutEnvX(PCTSTR pszName, PCTSTR pszValue)
{
    TCHAR *pBuffer = NULL;
    size_t size;

    TCHAR szError[1024];

    errno_t res = _tputenv_s(pszName, pszValue);
    if (res == 0)
    {
        _tgetenv_s(&size, NULL, 0, pszName);
        if (size == 0)
        {
            _tprintf(_T("getenv(%s, &size) failed.\n"), pszName);
        }
        else
        {
            //_tprintf(_T("getenv(%s, &size) == %zu.\n"), pszName, size);

            pBuffer = malloc(size * sizeof(TCHAR));
            _tgetenv_s(&size, pBuffer, size, pszName);
            _tprintf(_T("getenv(%s) == %s.\n"), pszName, pBuffer);
            free(pBuffer);
        }
    }
    else
    {
        _tcserror_s(szError, ARRAYSIZE(szError), res);
        _tprintf(_T("putenv(%s) failed(%d): %s.\n"), pszName, res, szError);
    }
}


void TestSetEnvironmentVariable(void)
{
    SetEnvironmentVariableX(_T("SETENV_VARIABLE1"), _T("Hello"));

    SetEnvironmentVariableX(_T("SETENV_VARIABLE2"), _T(""));
    SetEnvironmentVariableX(_T("SETENV_VARIABLE2"), _T("World"));

    SetEnvironmentVariableX(_T("SETENV_VARIABLE3"), _T(""));
    SetEnvironmentVariableX(_T("SETENV_VARIABLE3"), NULL);
    SetEnvironmentVariableX(_T("SETENV_VARIABLE3"), _T("World"));
}


void TestPutEnvX(void)
{
    PutEnvX(_T("PUTENV_VARIABLE1"), _T("Hello"));

    PutEnvX(_T("PUTENV_VARIABLE2"), _T(""));
    PutEnvX(_T("PUTENV_VARIABLE2"), _T("World"));

    PutEnvX(_T("PUTENV_VARIABLE3"), _T(""));
    //PutEnvX(_T("PUTENV_VARIABLE3"), NULL); // Assertion failure.
    PutEnvX(_T("PUTENV_VARIABLE3"), _T("World"));
}


int _tmain(void)
{
    TestSetEnvironmentVariable();
    TestPutEnvX();

    return 0;
}


// Output:

// On Win10:
/*
GetEnvironmentVariable(SETENV_VARIABLE1): Hello.
GetEnvironmentVariable(SETENV_VARIABLE2) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE2): World.
GetEnvironmentVariable(SETENV_VARIABLE3) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE3) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE3): World.
getenv(PUTENV_VARIABLE1) == Hello.
getenv(PUTENV_VARIABLE2, &size) failed.
getenv(PUTENV_VARIABLE2) == World.
getenv(PUTENV_VARIABLE3, &size) failed.
getenv(PUTENV_VARIABLE3) == World.
*/
// On Win7 SP1:
/*
GetEnvironmentVariable(SETENV_VARIABLE1): Hello.
GetEnvironmentVariable(SETENV_VARIABLE2) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE2): World.
GetEnvironmentVariable(SETENV_VARIABLE3) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE3) failed(0).
GetEnvironmentVariable(SETENV_VARIABLE3): World.
getenv(PUTENV_VARIABLE1) == Hello.
getenv(PUTENV_VARIABLE2, &size) failed.
getenv(PUTENV_VARIABLE2) == World.
getenv(PUTENV_VARIABLE3, &size) failed.
getenv(PUTENV_VARIABLE3) == World.
*/


// References:
// https://github.com/skywind3000/PyStand/issues/7
// https://github.com/reactos/reactos/blob/master/dll/win32/kernel32/client/environ.c
// https://github.com/reactos/reactos/blob/master/sdk/lib/rtl/env.c
// https://github.com/reactos/reactos/blob/master/sdk/lib/crt/misc/environ.c
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getenv-wgetenv?view=msvc-170
