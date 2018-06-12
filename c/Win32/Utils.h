#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

BOOL GetModulePath(HMODULE hModule, LPWSTR lpFilename, DWORD dwChars);
LPCWSTR JoinPath(LPWSTR lpPath, LPCWSTR lpBaseDir, LPCWSTR lpSubDir);

void ShowErrorMessage(HWND hWnd, LPCWSTR lpcszTitle, LPCWSTR lpcszFormat, ...);

LPWSTR TrimRight(LPWSTR lpStr);
BOOL EndsWithI(LPCWSTR lpStr, LPCWSTR lpPattern);

#ifdef __cplusplus
}
#endif