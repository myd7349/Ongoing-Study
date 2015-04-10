/*
2015-04-10T10:44+08:00
http://www.zhihu.com/question/29402649
*/
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

size_t get_bits_of_int_v1(void)
{
    int zen_of_life[] = {42, 0};
    return ((void *)(zen_of_life + 1) - (void *)zen_of_life) * 8;
}

int main()
{
    printf("%u\n", get_bits_of_int_v1());
    return 0;
}
