#pragma once

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
# define TCHAR_TO_ANSI(str) wchar_to_ansi((str))
# define ANSI_TO_TCHAR(str) ansi_to_wchar((str))

# define TCHAR_TO_UTF8(str) wchar_to_utf8((str))
# define UTF8_TO_TCHAR(u8s) utf8_to_wchar((u8s))

# define TCHAR_TO_ANSI_FREE(str) wconv_free((str))
# define ANSI_TO_TCHAR_FREE(str) wconv_free((str))
#else
# define TCHAR_TO_ANSI(str) (str)
# define ANSI_TO_TCHAR(str) (str)

# define TCHAR_TO_UTF8(str) ansi_to_utf8(str)
# define UTF8_TO_TCHAR(u8s) utf8_to_ansi(u8s)

# define TCHAR_TO_ANSI_FREE(str) ((void)(str))
# define ANSI_TO_TCHAR_FREE(str) ((void)(str))
#endif

#define TCHAR_TO_UTF8_FREE(str) wconv_free((str))
#define UTF8_TO_TCHAR_FREE(u8s) wconv_free((u8s))

char *wchar_to_ansi(const wchar_t *wstr);
wchar_t *ansi_to_wchar(const char *str);

char *wchar_to_utf8(const wchar_t *wstr);
wchar_t *utf8_to_wchar(const char *str);

char *ansi_to_utf8(const char *str);
char *utf8_to_ansi(const char *u8s);

void wconv_free(void *ptr);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

#include <string>

inline std::string WCharToAnsi(const wchar_t *wstr)
{
    std::string str;

    char *astr = wchar_to_ansi(wstr);
    if (astr != nullptr)
    {
        str = astr;
        wconv_free(astr);
    }

    return str;
}

inline std::string WCharToAnsi(const std::wstring &str)
{
    return WCharToAnsi(str.c_str());
}


inline std::wstring AnsiToWChar(const char *astr)
{
    std::wstring str;

    wchar_t *wstr = ansi_to_wchar(astr);
    if (wstr != nullptr)
    {
        str = wstr;
        wconv_free(wstr);
    }

    return str;
}


inline std::wstring AnsiToWChar(const std::string &str)
{
    return AnsiToWChar(str.c_str());
}


inline std::string WCharToUtf8(const wchar_t *wstr)
{
    std::string str;

    char *u8s = wchar_to_utf8(wstr);
    if (u8s != nullptr)
    {
        str = u8s;
        wconv_free(u8s);
    }

    return str;
}

inline std::string WCharToUtf8(const std::wstring &str)
{
    return WCharToUtf8(str.c_str());
}


inline std::wstring Utf8ToWChar(const char *u8s)
{
    std::wstring str;

    wchar_t *wstr = utf8_to_wchar(u8s);
    if (wstr != nullptr)
    {
        str = wstr;
        wconv_free(wstr);
    }

    return str;
}


inline std::wstring Utf8ToWChar(const std::string &str)
{
    return Utf8ToWChar(str.c_str());
}


inline std::string AnsiToUtf8(const char *astr)
{
    std::string str;

    char *u8s = ansi_to_utf8(astr);
    if (u8s != nullptr)
    {
        str = u8s;
        wconv_free(u8s);
    }

    return str;
}


inline std::string AnsiToUtf8(const std::string &str)
{
    return AnsiToUtf8(str.c_str());
}


inline std::string Utf8ToAnsi(const char *u8s)
{
    std::string str;

    char *astr = utf8_to_ansi(u8s);
    if (astr != nullptr)
    {
        str = astr;
        wconv_free(astr);
    }

    return str;
}


inline std::string Utf8ToAnsi(const std::string &str)
{
    return Utf8ToAnsi(str.c_str());
}


#ifdef _UNICODE
# define T2A(s) WCharToAnsi((s))
# define A2T(s) AnsiToWChar((s))
# define T2U(s) WCharToUtf8((s))
# define U2T(s) Utf8ToWChar((s))
#else
# define T2A(s) std::string((s))
# define A2T(s) std::string((s))
# define T2U(s) AnsiToUtf8((s))
# define U2T(s) Utf8ToAnsi((s))
#endif

#endif
