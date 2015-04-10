/*
2015-04-10T10:44+08:00
http://www.zhihu.com/question/29402649
*/
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

/*
http://stackoverflow.com/questions/6384856/how-to-know-size-of-int-without-sizeof
*/
size_t get_bits_of_int_v1(void)
{
    int zen_of_life[] = {42, 0};
    return ((void *)(zen_of_life + 1) - (void *)zen_of_life) * 8;
}

size_t get_bits_of_int_v2(void)
{
    struct Foo {
        int _;
        int __;
    };

    return offsetof(struct Foo, __) * 8;
}

/*
http://stackoverflow.com/questions/1219199/size-of-a-datatype-without-using-sizeof
*/
#define SIZEOF(type) ((size_t)(1 + (type *)0))
#define get_bits_of_int_v3() (SIZEOF(int) * 8)

size_t get_bits_of_int_v4(void)
{
#ifndef NDEBUG
    printf("%f\n", log2(INT_MAX)); // 0.000000 ?
    printf("%f\n", log2(UINT_MAX)); // 0.000000
#endif

    return (size_t)ceil(log2(UINT_MAX));
    return (int)log2(INT_MAX) + 2;
    return (int)log2(UINT_MAX) + 1;
}

int main()
{
    printf("%u\n", get_bits_of_int_v1());
    printf("%u\n", get_bits_of_int_v2());
    printf("%u\n", get_bits_of_int_v3());
    printf("%u\n", get_bits_of_int_v4());
    printf("%u\n", SIZEOF(double));

    return 0;
}
