#include "Utils.h"

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")


BOOL GetModulePath(HMODULE hModule, LPWSTR lpFilename, DWORD dwChars)
{
    DWORD dwRes;
    WCHAR *pLastPathSep = NULL;

    assert(lpFilename != NULL && dwChars > 1);

    dwRes = GetModuleFileName(hModule, lpFilename, dwChars);
    if (dwRes == 0 || dwRes == dwChars)
        return FALSE;

    pLastPathSep = StrRChrW(lpFilename, NULL, L'\\');
    if (pLastPathSep == NULL)
        return FALSE;

    *(pLastPathSep + 1) = L'\0';
    return TRUE;
}


LPCWSTR JoinPath(LPWSTR lpPath, LPCWSTR lpBaseDir, LPCWSTR lpSubDir)
{
    return PathCombineW(lpPath, lpBaseDir, lpSubDir);
}


void ShowErrorMessage(HWND hWnd, LPCWSTR lpcszTitle, LPCWSTR lpcszFormat, ...)
{
    WCHAR szBuffer[1024] = L"";
    va_list vargs;
    int nRes;

    assert(lpcszFormat != NULL);

    va_start(vargs, lpcszFormat);
    nRes = vswprintf(szBuffer, _countof(szBuffer), lpcszFormat, vargs);
    va_end(vargs);

    MessageBoxW(
        hWnd,
        szBuffer,
        lpcszTitle == NULL ? L"Error" : lpcszTitle,
        MB_OK | MB_ICONERROR);
}


LPWSTR TrimRight(LPWSTR lpStr)
{
    LPWSTR lpChar;

    assert(lpStr != NULL);

    lpChar = lpStr + wcslen(lpStr) - 1;

    while (lpChar >= lpStr && iswspace(*lpChar))
        lpChar--;

    if (iswspace(*++lpChar))
        *lpChar = L'\0';

    return lpStr;
}


BOOL EndsWith(LPCWSTR lpStr, LPCWSTR lpPattern)
{
    size_t cchStrLength;
    size_t cchPatternLength;

    assert(lpStr != NULL);
    assert(lpPattern != NULL);
    if (lpPattern[0] == L'\0')
        return TRUE;

    cchStrLength = wcslen(lpStr);
    cchPatternLength = wcslen(lpPattern);
    if (cchStrLength < cchPatternLength)
        return FALSE;

    return wcscmp(lpStr + (cchStrLength - cchPatternLength), lpPattern);
}


BOOL EndsWithI(LPCWSTR lpStr, LPCWSTR lpPattern)
{
    size_t cchStrLength;
    size_t cchPatternLength;

    assert(lpStr != NULL);
    assert(lpPattern != NULL);
    if (lpPattern[0] == L'\0')
        return TRUE;

    cchStrLength = wcslen(lpStr);
    cchPatternLength = wcslen(lpPattern);
    if (cchStrLength < cchPatternLength)
        return FALSE;

    return _wcsicmp(lpStr + (cchStrLength - cchPatternLength), lpPattern);
}


// References:
// Ongoing-Study/cpp/strutils.hpp
