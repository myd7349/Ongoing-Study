// 2018-03-01T15:11+08:00
#include <assert.h>
#include <math.h>
#include <stdlib.h>


extern const char *reverse(char *); // See `reverse.c`


const char *itoa(int n, int base, char *buffer, size_t size)
{
    size_t i = 0;
    size_t max_digits;
    div_t quot_rem = { n, 0 };

    assert(base > 1 && base <= 36);

    if (buffer == NULL || size == 0)
        return "";

    if (size == 1 || (n < 0 && size == 2))
    {
        buffer[0] = '\0';
        return "";
    }

    max_digits = size - 1 - (n < 0 ? 1 : 0);

    do
    {
        quot_rem = div(quot_rem.quot, base);
        buffer[i++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[abs(quot_rem.rem)];
    } while (quot_rem.quot != 0 && i < max_digits);

    if (quot_rem.quot == 0)
    {
        if (n < 0)
            buffer[i++] = '-';

        buffer[i] = '\0';

        return reverse(buffer);
    }
    else
    {
        buffer[0] = '\0';
        return "";
    }
}


// References:
// http://en.cppreference.com/w/c/numeric/math/div
// Ongoing-study/python/modulo_operation.py
// https://github.com/miloyip/itoa-benchmark
// https://github.com/drh/cii/blob/master/src/xp.c#L250
// https://github.com/drh/cii/blob/master/src/ap.c#L368
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/signalhandler.cc#L85-L145
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/symbolize.cc#L663-L729
