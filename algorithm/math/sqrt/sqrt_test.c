#include <math.h>
#include <stdio.h>

#include "../../algutils.h"
#include "sqrt.h"


#define TEST(x) printf("sqrt(" STR(x) ")=%f\n", fsqrt(x))



int main()
{
    TEST(0.0);
    TEST(1.0);
    TEST(2.0);
    TEST(3.0);
    TEST(4.0);
    TEST(100.0);
    TEST(-1.0);
    TEST(NAN);
    TEST(INFINITY);
    TEST(-INFINITY);

    return 0;
}
