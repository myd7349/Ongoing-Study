// 2017-11-26T15:13+08:00
#include <stdio.h>

#include "../../algutils.h"
#include "linear_search.h"


int main()
{
    int x[] = { -42, 3, 7, 9, 11 };

#define TEST_CASE(value) \
{ \
    int pos = linear_searchi(ARRAY(x), value); \
    if (pos >= 0) \
        printf("Found " STR(value) " at %d in array ", pos); \
    else \
        printf("Couldn't found " STR(value) " in array "); \
    \
    printvi(ARRAY(x)); \
}

    TEST_CASE(11);
    TEST_CASE(-42);
    TEST_CASE(3);
    TEST_CASE(100);

    return 0;
}
