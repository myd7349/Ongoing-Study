#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

std::basic_string<TCHAR> TranslateError(
    DWORD dwErrorCode = GetLastError(),
    DWORD dwLangID = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
