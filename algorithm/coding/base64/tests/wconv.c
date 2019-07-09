#include "wconv.h"

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


// Copy from:
// https://github.com/pbatard/libwdi/blob/master/libwdi/msapi_utf8.h

#define wchar_to_utf8_no_alloc(wsrc, dest, dest_size) \
    WideCharToMultiByte(CP_UTF8, 0, (wsrc), -1, (dest), (dest_size), NULL, NULL)
#define utf8_to_wchar_no_alloc(src, wdest, wdest_size) \
    MultiByteToWideChar(CP_UTF8, 0, src, -1, wdest, wdest_size)


/*
 * Converts an UTF-16 string to UTF8 (allocate returned string)
 * Returns NULL on error
 */
char *wchar_to_utf8(const wchar_t *wstr)
{
    char *str = NULL;

    // Find out the size we need to allocate for our converted string
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (size <= 1)	// An empty string would be size 1
        return NULL;

    if ((str = (char *)calloc(size, 1)) == NULL)
        return NULL;

    if (wchar_to_utf8_no_alloc(wstr, str, size) != size) {
        free(str);
        return NULL;
    }

    return str;
}


/*
 * Converts an UTF8 string to UTF-16 (allocate returned string)
 * Returns NULL on error
 */
wchar_t *utf8_to_wchar(const char *str)
{
    int size = 0;
    wchar_t* wstr = NULL;

    if (str == NULL)
        return NULL;

    // Find out the size we need to allocate for our converted string
    size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    if (size <= 1)	// An empty string would be size 1
        return NULL;

    if ((wstr = (wchar_t *)calloc(size, sizeof(wchar_t))) == NULL)
        return NULL;

    if (utf8_to_wchar_no_alloc(str, wstr, size) != size) {
        free(wstr);
        return NULL;
    }

    return wstr;
}
