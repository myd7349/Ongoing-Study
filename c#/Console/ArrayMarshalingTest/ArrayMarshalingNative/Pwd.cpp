#define PWD_API __declspec(dllexport)
#include "Pwd.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <direct.h>

char *GetCurrentDirectory(char *buf, int len)
{
    assert(buf != NULL && len > 0);
    if (buf == NULL || len <= 0)
    {
        // When a NULL argument is given as buffer,
        // _getcwd may call malloc to allocate memory.
        // I don't think this is a good idea.
        // So please always give me a writable buffer.
        return NULL;
    }

    char *wd = _getcwd(buf, len);
    assert(buf == wd);
    if (errno != 0)
        memset(buf, 0, len);

#ifndef NDEBUG
    printf("[Unmanaged::Debug] %s\n", wd);
#endif

    return wd;
}