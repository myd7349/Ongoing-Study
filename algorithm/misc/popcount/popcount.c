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
