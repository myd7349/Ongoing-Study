// 2015-06-04T13:59+08:00
// gcc: -std=c99

#include <stdio.h>
#include <string.h>

#include "../../common.h"

int main()
{
    double data[] = {0, 1, 2, 3, 4, 5};
    memmove(data, data + 1, (ARRAYSIZE(data) - 1) * sizeof(data[0]));

    // C99 allows 'for' loop initial declarations
    for (int i = 0; i < 6; ++i) {
        printf("%g\n", data[i]);
    }

    return 0;
}
