#include <stdint.h>

#include "../../bitutils.h"


union Foo
{
    uint32_t i;
    float f;
};


int main(void)
{
    union Foo foo1;
    union Foo foo2;

    foo1.i = 0;
    foo2.f = 0.0;

    PRINT_BITS_EX(foo1.i, 8, 1);
    PRINT_BITS_EX(foo2.i, 8, 1);

    return 0;
}
