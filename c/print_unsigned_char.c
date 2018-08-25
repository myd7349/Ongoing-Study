// 2018-06-30T14:45+08:00
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>


int main()
{
    char ch = 212;

    printf("%d\n", ch);
    printf("%u\n", ch);
    printf("%d\n", (unsigned)(unsigned char)ch);
    printf("%" PRIu8 "\n", ch);

    return 0;
}

/*
Output:
-44
4294967252
212
*/

// References:
// https://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c
// https://stackoverflow.com/questions/8132399/how-to-printf-uint64-t-fails-with-spurious-trailing-in-format
// https://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c
