#include "xassert.h"

#include <stdio.h>
#include <stdlib.h>


void assert_impl(const char *file, int line, const char *func, const char *expr)
{
    fprintf(stderr, "Assertion FAILED|%s(%d)|%s: %s",
        file, line, func, expr);

    exit(EXIT_FAILURE);
}


// References:
// C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src\assert.c
// https://github.com/ericherman/eh-no-libc/blob/master/src/assert.c
// https://stackoverflow.com/questions/9701229/c-assert-implementation-in-assert-h
