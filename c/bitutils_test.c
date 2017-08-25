// 2017-08-25T15:03+08:00
#include "bitutils.h"

typedef unsigned char uchar;

int main()
{
    uchar initial_status = 0x7e;

    uchar high = initial_status;
    uchar low = initial_status;

    signed char hmask = 0x8f;
    signed char lmask = 0xf1;

    int i;

    PRINT_BITS(initial_status);
    putchar('\n');

    for (i = 0; i < 3; ++i)
    {
        SWAP_BIT(initial_status, i, i + 1);
        SWAP_BIT(initial_status, 7 - i, 7 - i - 1);
        PRINT_BITS(initial_status);
        putchar('\n');
    }

    puts("===============================================================================");

    initial_status = 0x7e;

    PRINT_BITS(initial_status);
    putchar('\n');

    for (i = 0; i < 3; ++i)
    {
        initial_status = (uchar)
            (
                ((hmask | (high >>= 1)) & 0xf0) |
                ((lmask | (low << 1)) & 0x0f)
            );

        PRINT_BITS(initial_status);
        putchar('\n');

        hmask >>= 1;
        low = initial_status;
    }

    getchar();

    return 0;
}