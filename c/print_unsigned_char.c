// 2018-06-30T14:45+08:00
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


int main()
{
    char ch = 212;

    printf("%d\n", ch);
    printf("%u\n", ch);
    printf("%d\n", (unsigned)(unsigned char)ch);
    printf("%" PRIu8 "\n", ch);

    ch = 0xFE;

    printf("\n%d\n", ch);
    printf("%u\n", ch);
    printf("%d\n", (unsigned)(unsigned char)ch);
    printf("%hhu\n", ch);
    //  warning: invalid suffix on literal;
    // C++11 requires a space between literal and string macro [-Wliteral-suffix]
    //printf("%"PRIu8"\n", ch);
    printf("%" PRIu8 "\n", ch);

    ch = UINT8_C(0xFF);

    printf("\n%d\n", ch);
    printf("%u\n", ch);
    printf("%d\n", (unsigned)(unsigned char)ch);
    printf("%hhu\n", ch);
    printf("%" PRIu8 "\n", ch);

    ch = 0xCC;
    printf("ch == 0xCC? %d\n", ch == 0xCC);
    printf("ch == 0xCC? %d\n", ch == (char)0xCC);

    return 0;
}

/*
Output:

VS2017 x86 + Win10 x64:

-44
4294967252
212
212

-2
4294967294
254
254
254

*/

// References:
// https://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c
// https://stackoverflow.com/questions/8132399/how-to-printf-uint64-t-fails-with-spurious-trailing-in-format
// https://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c
// https://stackoverflow.com/questions/14535556/why-doesnt-priu64-work-in-this-code
// https://stackoverflow.com/questions/12120426/how-do-i-print-uint32-t-and-uint16-t-variables-value
// https://stackoverflow.com/questions/6993132/format-specifiers-for-uint8-t-uint16-t
