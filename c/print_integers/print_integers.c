#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


int main()
{
    unsigned char ch = 212;
    int64_t int64 = 1;
    long int long_int = 1;
    long long int long_long_int = 1;

    printf("%" PRIu8 "\n", ch);

    printf("sizeof(int): %zu, Example: %d\n", sizeof(int), 1);
    printf("sizeof(long int): %zu, Example: %ld\n", sizeof(long int), long_int);
    printf("sizeof(long long int): %zu, Example: %lld\n", sizeof(long long int), long_long_int);
    printf("sizeof(int64_t): %zu, Example: %" PRId64 "\n", sizeof(int64_t), int64);

    return 0;
}

// References:
// https://stackoverflow.com/questions/8132399/how-to-printf-uint64-t-fails-with-spurious-trailing-in-format
// https://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c
