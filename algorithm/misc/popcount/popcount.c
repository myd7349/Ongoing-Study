// 2016-07-24T19:27+08:00
#include <stdio.h>

static unsigned int popcount(unsigned int value)
{
    unsigned int count = 0;

    for (; value; ++count)
        value &= value - 1;

    return count;
}

#define DUMP_POPCOUNT(value) printf("popcount(%#x): %u\n", (unsigned int)value, popcount((unsigned int)value));

int main()
{
    DUMP_POPCOUNT(0);
    DUMP_POPCOUNT(1);
    DUMP_POPCOUNT(-1);

    return 0;
}

// References:
// [How to count the number of set bits in a 32-bit integer?](http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer)
// [Hamming weight](https://en.wikipedia.org/wiki/Hamming_weight)
//
// https://www.zhihu.com/question/51959388
// GCC/Clang: __builtin_popcount(unsigned int) / __builtin_popcountl(unsigned long)
// MSVC: __popcnt(unsigned int)
// ICC: _mm_popcnt_u32(unsigned int)
//
// https://www.zhihu.com/question/52726115
// https://blog.csdn.net/zotin/article/details/5885131
// https://github.com/arximboldi/immer/blob/a28718c0511ae41503b1c6ef36f4b5368fa717ba/immer/detail/hamts/bits.hpp#L73-L103
// https://github.com/microsoft/angle/blob/c61d0488abd9663e0d4d2450db7345baa2c0dfb6/src/common/mathutil.h#L885-L920
// Windows Terminal relays on: https://github.com/kimwalisch/libpopcnt
