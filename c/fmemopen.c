#include "fmemopen.h"

#include <string.h>

#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <windows.h>


char tmp_file_name[MAX_PATH];


// https://github.com/martinh/libconfuse/blob/2f7d120e170351cf424845ed27a532cce443247d/src/fmemopen.c#L119-L158
FILE *fmemopen_v1(void *buf, size_t len, const char *type)
{
    int fd;
    FILE *fp;
    char tp[MAX_PATH - 13];
    char fn[MAX_PATH + 1];
    HANDLE h;

    if (!GetTempPath(sizeof(tp), tp))
        return NULL;

    if (!GetTempFileName(tp, "confuse", 0, fn))
        return NULL;

    strcpy(tmp_file_name, fn);

    printf("[DBG] %s(%d): Temp file name: %s\n",
        __FUNCTION__, __LINE__, fn);

    h = CreateFile(fn, GENERIC_READ | GENERIC_WRITE, 0, NULL,
               CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);
    if (INVALID_HANDLE_VALUE == h)
        return NULL;

    fd = _open_osfhandle((intptr_t)h, _O_APPEND);
    if (fd < 0) {
        CloseHandle(h);
        return NULL;
    }

    fp = _fdopen(fd, "w+");
    if (!fp) {
        CloseHandle(h);
        return NULL;
    }

    fwrite(buf, len, 1, fp);
    rewind(fp);

    return fp;
}


// https://github.com/DanBloomberg/leptonica/blob/4972d55fcddee5c51f393747848c87fa54a64a78/src/utils2.c#L3254-L3312
static const char *l_makeTempFilename(char fname[MAX_PATH])
{
    FILE *fp;
    if (!CreateDirectory("/tmp", NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
        return NULL;
    if (GetTempFileName("/tmp", "lp.", 0, fname) == 0)
        return NULL;
    if ((fp = fopen(fname, "wb")) == NULL)
        return NULL;
    fclose(fp);
    return fname;
}


// https://github.com/DanBloomberg/leptonica/blob/4972d55fcddee5c51f393747848c87fa54a64a78/src/utils2.c#L1926-L1973
/*--------------------------------------------------------------------*
 *                Opening a windows tmpfile for writing               *
 *--------------------------------------------------------------------*/
/*!
 * \brief   fopenWriteWinTempfile()
 *
 * \return  file stream, or NULL on error
 *
 * <pre>
 * Notes:
 *      (1) The Windows version of tmpfile() writes into the root
 *          C:\ directory, which requires admin privileges.  This
 *          function provides an alternative implementation.
 * </pre>
 */
static FILE *fopenWriteWinTempfile(const char *mode)
{
#ifdef _WIN32
    int  handle;
    FILE    *fp;
    char     filename[MAX_PATH];

    if (l_makeTempFilename(filename) == NULL)
        return NULL;

    strcpy(tmp_file_name, filename);

    printf("[DBG] %s(%d): Temp file name: %s\n",
        __FUNCTION__, __LINE__, filename);

    handle = _open(filename, _O_CREAT | _O_RDWR | _O_SHORT_LIVED |
                   _O_TEMPORARY | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (handle == -1)
        return NULL;

    if ((fp = _fdopen(handle, mode)) == NULL)
        return NULL;

    return fp;
#else
    return NULL;
#endif  /*  _WIN32 */
}


// https://github.com/DanBloomberg/leptonica/blob/4972d55fcddee5c51f393747848c87fa54a64a78/src/utils2.c#L1882-L1923
FILE *fmemopen_v2(void *data, size_t size, const char *mode)
{
    FILE  *fp;

    if (!data)
        return NULL;

#if HAVE_FMEMOPEN
    if ((fp = fmemopen(data, size, mode)) == NULL)
        return NULL;
#else /* work-around: writing to a temp file */
#if defined(_WIN32) && !defined(USE_STDC_TMPFILE)
    if ((fp = fopenWriteWinTempfile(mode)) == NULL)
        return NULL;
#else
    if ((fp = tmpfile()) == NULL)
        return NULL;
#endif /* _WIN32 */
    fwrite(data, 1, size, fp);
    rewind(fp);
#endif /* HAVE_FMEMOPEN */

    return fp;
}
