// 2018-03-01T15:11+08:00
#include <assert.h>
#include <math.h>
#include <stdlib.h>


extern const char *reverse(char *); // See `reverse.c`


const char *itoa(int n, int base, char *buffer, size_t size)
{
    char *p = buffer;
    int negative = n < 0;

    assert(base > 1 && base <= 36);
    assert(buffer != NULL && size > 1);

    do
    {
        int rem = n % base;
        *p++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[abs(rem)];
        n /= base;
    } while (n != 0);

    if (negative)
        *p++ = '-';

    *p = '\0';

    return reverse(buffer);
}


// References:
// http://en.cppreference.com/w/c/numeric/math/div
// Ongoing-study/python/modulo_operation.py
// https://github.com/miloyip/itoa-benchmark
// https://github.com/drh/cii/blob/master/src/xp.c#L250
// https://github.com/drh/cii/blob/master/src/ap.c#L368
