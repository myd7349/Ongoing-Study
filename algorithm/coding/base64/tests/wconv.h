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
# define UTF8_TO_TCHAR(u8s)  utf8_to_wchar((u8s))
#else
# define TCHAR_TO_ANSI(str) (str)
# define ANSI_TO_TCHAR(str) (str)

# define TCHAR_TO_UTF8(str) (str)
# define UTF8_TO_TCHAR(u8s)  (u8s)
#endif

char *wchar_to_ansi(const wchar_t *wstr);
wchar_t *ansi_to_wchar(const char *str);

char *wchar_to_utf8(const wchar_t *wstr);
wchar_t *utf8_to_wchar(const char *str);

#ifdef __cplusplus
}
#endif
