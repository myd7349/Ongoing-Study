#include <stdint.h>
#include <stdio.h>

int main()
{
    union
    {
        uint8_t c[sizeof(uint16_t)];
        uint16_t s;
    } un;

    un.s = 0x0201;

    if (un.c[0] == 1 && un.c[1] == 2)
        puts("Little Endian");
    else if (un.c[0] == 2 && un.c[1] == 1)
        puts("Big Endian");
    else
        puts("Unknown endianess!");

    return 0;
}

// References:
// UNPv1, Chapter 3
