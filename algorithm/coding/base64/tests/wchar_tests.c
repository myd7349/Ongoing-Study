#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../base64.h"
#include "wconv.h"


void do_test(const _TCHAR *str)
{
    char buffer[256];
    size_t olen = sizeof(buffer);

#ifdef _UNICODE
    char *u8str = TCHAR_TO_UTF8(str);
    _putts(_T("------------------------------------------------------------"));

    if (u8str == NULL)
    {
        _ftprintf(stderr, _T("Failed to convert input string to utf-8 string!\n"));
        return;
    }
#else
    const char *u8str = str;
#endif

    if (easy_base64_encode(u8str, strlen(u8str), buffer, olen) != NULL)
    {
        _tprintf(
            _T("Original: %s\n")
#ifdef _UNICODE
            _T("Base64  : %S\n")
#else
            _T("Base64  : %s\n")
#endif
            ,
            str,
            buffer
        );
    }
    else
    {
        _ftprintf(stderr, _T("Failed to encode the input string!\n"));
    }

#ifdef _UNICODE
    free(u8str);
#endif
}


int _tmain(int argc, _TCHAR *argv[])
{
#ifdef _UNICODE
    _tsetlocale(LC_ALL, _T(""));
#endif

    do_test(_T("Good morning."));
    do_test(_T("おはよう"));
    do_test(_T("早上好！"));

    return 0;
}


// References:
// https://stackoverflow.com/questions/10439680/wchar-t-and-encoding
// https://stackoverflow.com/questions/3996026/what-is-the-default-encoding-for-c-strings
// https://stackoverflow.com/questions/6794590/how-does-file-encoding-affect-c11-string-literals

/*
> wchar_tests.exe
------------------------------------------------------------
Original: Good morning.
Base64  : R29vZCBtb3JuaW5nLg==
------------------------------------------------------------
Original: おはよう
Base64  : 44GK44Gv44KI44GG
------------------------------------------------------------
Original: 早上好！
Base64  : 5pep5LiK5aW977yB

> char_tests.exe
Original: Good morning.
Base64  : R29vZCBtb3JuaW5nLg==
Original: おはよう
Base64  : pKqkz6TopKY=
Original: 早上好！
Base64  : 1OfJz7rDo6E=

> py
>>> from base64 import *
>>> b64encode('早上好！'.encode('utf-8'))
b'5pep5LiK5aW977yB'
>>> b = 
>>> b64encode('早上好！'.encode('gbk'))
b'1OfJz7rDo6E='
*/
