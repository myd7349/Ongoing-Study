#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>


int main(void)
{
#ifdef _MSC_VER
    uint16_t x = _UI16_MAX;
#else
    uint16_t x = USHRT_MAX;
#endif

    printf("%" PRIu16 "\n", x + 1);
    printf("%d\n", x + 1 == 0);
    printf("%d\n", (uint16_t)(x + 1) == 0);
    printf("%d\n", x + 1ui16 == 0ui16);

    return 0;
}


// References:
// [C/C++ unsigned integer overflow](https://stackoverflow.com/questions/16056758/c-c-unsigned-integer-overflow)
