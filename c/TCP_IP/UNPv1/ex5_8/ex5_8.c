#include <stdio.h>

#include <endian/endian.h>

#include "../../../bitutils.h"


#if !(PSNIP_ENDIAN_ORDER == PSNIP_ENDIAN_LITTLE)
# error This program is supposed to run on little endian machines.
#endif


#define PP(prefix, val) \
    do \
    { \
        printf(prefix ": "); \
        PRINT_BITS_EX(val, 8, 0); \
        printf(" (%d)\n", (val)); \
    } while (0)


void test(psnip_int32_t x, psnip_int32_t y)
{
    puts("==================================================");

    psnip_int32_t sum;

    puts("Client's view:");
    PP("x", x);
    PP("y", y);

    puts("Server's view:");
    x = psnip_endian_be32(x);
    y = psnip_endian_be32(y);
    sum = x + y;
    PP("x", x);
    PP("y", y);
    PP("+", sum);

    puts("Client's view:");
    sum = psnip_builtin_bswap32(sum);
    PP("+", sum);
}

int main()
{
    test(1, 2);
    test(-22, -77);

    return 0;
}


/*
==================================================
Client's view:
x: 00000000 00000000 00000000 00000001 (1)
y: 00000000 00000000 00000000 00000010 (2)
Server's view:
x: 00000001 00000000 00000000 00000000 (16777216)
y: 00000010 00000000 00000000 00000000 (33554432)
+: 00000011 00000000 00000000 00000000 (50331648)
Client's view:
+: 00000000 00000000 00000000 00000011 (3)
==================================================
Client's view:
x: 11111111 11111111 11111111 11101010 (-22)
y: 11111111 11111111 11111111 10110011 (-77)
Server's view:
x: 11101010 11111111 11111111 11111111 (-352321537)
y: 10110011 11111111 11111111 11111111 (-1275068417)
+: 10011110 11111111 11111111 11111110 (-1627389954)
Client's view:
+: 11111110 11111111 11111111 10011110 (-16777314)
*/
