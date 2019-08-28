#include "wconv.h"

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#define wchar_to_multibyte_no_alloc(wsrc, cp, dest, dest_size) \
    WideCharToMultiByte((cp), 0, (wsrc), -1, (dest), (dest_size), NULL, NULL)
#define multibyte_to_wchar_no_alloc(src, cp, wdest, wdest_size) \
    MultiByteToWideChar((cp), 0, src, -1, wdest, wdest_size)


// _AtlGetConversionACP
static inline UINT get_conversion_acp(void)
{
#ifdef CONVERSION_DONT_USE_THREAD_LOCALE
    return CP_ACP;
#else
    return CP_THREAD_ACP;
#endif
}


static char *wchar_to_multibyte(const wchar_t *wstr, UINT code_page)
{
    char *str = NULL;

    // Find out the size we need to allocate for our converted string
    int size = WideCharToMultiByte(code_page, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (size <= 1)	// An empty string would be size 1
        return NULL;

    if ((str = (char *)calloc(size, 1)) == NULL)
        return NULL;

    if (wchar_to_multibyte_no_alloc(wstr, code_page, str, size) != size) {
        free(str);
        return NULL;
    }

    return str;
}


static wchar_t *multibyte_to_wchar(const char *str, UINT code_page)
{
    int size = 0;
    wchar_t* wstr = NULL;

    if (str == NULL)
        return NULL;

    // Find out the size we need to allocate for our converted string
    size = MultiByteToWideChar(code_page, 0, str, -1, NULL, 0);
    if (size <= 1)	// An empty string would be size 1
        return NULL;

    if ((wstr = (wchar_t *)calloc(size, sizeof(wchar_t))) == NULL)
        return NULL;

    if (multibyte_to_wchar_no_alloc(str, code_page, wstr, size) != size) {
        free(wstr);
        return NULL;
    }

    return wstr;
}


char *wchar_to_ansi(const wchar_t *wstr)
{
    return wchar_to_multibyte(wstr, get_conversion_acp());
}


wchar_t *ansi_to_wchar(const char *str)
{
    return multibyte_to_wchar(str, get_conversion_acp());
}


/*
 * Converts an UTF-16 string to UTF8 (allocate returned string)
 * Returns NULL on error
 */
char *wchar_to_utf8(const wchar_t *wstr)
{
    return wchar_to_multibyte(wstr, CP_UTF8);
}


/*
 * Converts an UTF8 string to UTF-16 (allocate returned string)
 * Returns NULL on error
 */
wchar_t *utf8_to_wchar(const char *u8s)
{
    return multibyte_to_wchar(u8s, CP_UTF8);
}


char *ansi_to_utf8(const char *str)
{
    char *u8s = NULL;

    wchar_t *wstr = ansi_to_wchar(str);
    if (wstr != NULL)
    {
        u8s = wchar_to_utf8(wstr);
        free(wstr);
    }

    return u8s;
}


char *utf8_to_ansi(const char *u8s)
{
    char *str;

    wchar_t *wstr = utf8_to_wchar(u8s);
    if (wstr != NULL)
    {
        str = wchar_to_ansi(wstr);
        free(wstr);
    }

    return str;
}


// References:
// https://github.com/pbatard/libwdi/blob/master/libwdi/msapi_utf8.h
// atlconv.h
// https://stackoverflow.com/questions/2108336/converting-multibyte-characters-to-utf-8
