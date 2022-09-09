#include <stdint.h>
#include <stdio.h>

#define BIN(x) 0b##x
#define BIN_v2(x) u32_to_bin((x))


static uint32_t u32_to_bin(uint32_t x)
{
    uint32_t b = 0;
    uint32_t factor = 1;

    while (x != 0)
    {
        b += (x % 10) * factor;
        x /= 10;

        factor <<= 1;
    }

    return b;
}


int main(void)
{
    printf("%X\n", BIN(11111001));
    printf("%X\n", BIN(11111001));

    return 0;
}


// References:
// [Can I use a binary literal in C or C++?](https://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c)
// [Binary literals?](https://stackoverflow.com/questions/537303/binary-literals)
// [C Program to Convert Binary Number to Decimal and vice-versa](https://www.programiz.com/c-programming/examples/binary-decimal-convert)
// [Binary Literals in C](https://embeddedgurus.com/barr-code/2009/09/binary-literals-in-c/)
// [assigning a variable using binary format - 0B causing error in ARM Keil uVision](https://stackoverflow.com/questions/66281737/assigning-a-variable-using-binary-format-0b-causing-error-in-arm-keil-uvision)
// [Why doesn't C have binary literals?](https://stackoverflow.com/questions/18244726/why-doesnt-c-have-binary-literals)
