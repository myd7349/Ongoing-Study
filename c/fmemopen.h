#pragma once

#include <stddef.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"
{
#endif

FILE *fmemopen_v1(void *buf, size_t len, const char *type);

FILE *fmemopen_v2(void *data, size_t size, const char *mode);

extern char tmp_file_name[];

#ifdef __cplusplus
}
#endif
