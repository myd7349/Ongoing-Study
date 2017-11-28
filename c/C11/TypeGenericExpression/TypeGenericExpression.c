// 2017-11-28T09:42+08:00
// _Generic:
// GCC: 4.9 or above
// clang:
// MSVC:
#include <stdio.h>

#include "../../../algorithm/graphics/lerp/lerp.h"


// See [3]
#define printf_dec_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")

#define print(x) printf(printf_dec_format(x), x)
#define println(x) (printf(printf_dec_format((x)), (x)), printf("\n"))

#define decltype(x) _Generic((x), \
    char: char, \
    short: short, \
    int: int, \
    long int: long int, \
    float: float, \
    double: double, \
    long double: long double, \
    default: void)


int main()
{
    // Generic selection is a primary expression.
    //decltype(0) x;

    println(lerp(0, 10, 5));
    println(lerp_fn((int)0)(1.0, 1.0, 0.0));
    println(lerp(0.0f, 1.0f, 0.5f));

    //lerp_fn(int)(1.0, 1.0, 0.0);

    return 0;
}

// References:
// [1] https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29
// [2] https://gcc.gnu.org/wiki/C11Status
// [3] http://www.robertgamble.net/2012/01/c11-generic-selections.html
