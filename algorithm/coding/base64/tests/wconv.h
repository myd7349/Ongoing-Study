#pragma once

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
# define TCHAR_TO_UTF8(wstr) wchar_to_utf8((wstr))
# define UTF8_TO_TCHAR(u8s)  utf8_to_wchar((u8s))
#else
# define TCHAR_TO_UTF8(wstr) (wstr)
# define UTF8_TO_TCHAR(u8s)  (u8s)
#endif

char *wchar_to_utf8(const wchar_t *wstr);

wchar_t *utf8_to_wchar(const char *str);

#ifdef __cplusplus
}
#endif
