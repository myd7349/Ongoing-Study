// 2018-06-30T14:45+08:00
#include <stdio.h>


int main()
{
    char ch = 212;

    printf("%d\n", ch);
    printf("%u\n", ch);
    printf("%d\n", (unsigned)(unsigned char)ch);

    return 0;
}

/*
Output:
-44
4294967252
212
*/

// References:
//https://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c
