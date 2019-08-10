#include "../xassert.h"

int main(void)
{
    xassert(10 + 2 == 11);
    xverify(1 > 2);

    return 0;
}
