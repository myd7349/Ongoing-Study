#pragma once

#include <stddef.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _UNICODE
# define TCHAR_TO_ANSI(str) wchar_to_ansi((str))
# define ANSI_TO_TCHAR(str) ansi_to_wchar((str))

# define TCHAR_TO_UTF8(str) wchar_to_utf8((str))
# define UTF8_TO_TCHAR(u8s) utf8_to_wchar((u8s))

# define TCHAR_TO_ANSI_FREE(str) free((str))
# define ANSI_TO_TCHAR_FREE(str) free((str))
#else
# define TCHAR_TO_ANSI(str) (str)
# define ANSI_TO_TCHAR(str) (str)

# define TCHAR_TO_UTF8(str) ansi_to_utf8(str)
# define UTF8_TO_TCHAR(u8s) utf8_to_ansi(u8s)

# define TCHAR_TO_ANSI_FREE(str) ((void)(str))
# define ANSI_TO_TCHAR_FREE(str) ((void)(str))
#endif

#define TCHAR_TO_UTF8_FREE(str) free((str))
#define UTF8_TO_TCHAR_FREE(u8s) free((u8s))

char *wchar_to_ansi(const wchar_t *wstr);
wchar_t *ansi_to_wchar(const char *str);

char *wchar_to_utf8(const wchar_t *wstr);
wchar_t *utf8_to_wchar(const char *str);

char *ansi_to_utf8(const char *str);
char *utf8_to_ansi(const char *u8s);

#ifdef __cplusplus
}
#endif
