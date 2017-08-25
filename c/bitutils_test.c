// 2017-08-25T15:03+08:00
#include "bitutils.h"

typedef unsigned char uchar;

int main()
{
    uchar initial_status = 0x7e;

    //uchar lmask = 0x8f;
    //uchar hmask = 0xf1;

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

    getchar();

    return 0;
}