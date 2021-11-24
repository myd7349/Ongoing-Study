/* Copyright (C) 1991-2021 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <string.h>

#include "strdup.h"


#if !defined(HAVE_STRDUP) && !defined(HAVE__STRDUP)
char *strdup(const char *str)
{
    size_t length = strlen(str) + 1;

    void *new = malloc(length);
    if (new == NULL)
        return NULL;

    return memcpy(new, str, length);
}
#endif


// References:
// https://github.com/bminor/glibc/blob/master/string/strdup.c
// [strdup](https://github.com/snowballstem/snowball/pull/136)
// [strdup](https://en.cppreference.com/w/c/experimental/dynamic/strdup)
// https://github.com/clibs/strdup/blob/master/strdup.c
// https://github.com/lattera/glibc/blob/master/string/strdup.c
// [strlen not checking for NULL](https://stackoverflow.com/questions/5796103/strlen-not-checking-for-null)
// https://github.com/ros2/rcutils/blob/master/src/strdup.c
// https://github.com/curl/curl/blob/master/lib/strdup.c
