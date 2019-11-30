#include <stdio.h>


int main()
{
    int apricot[2][3][5];
    int (*r)[5] = apricot[0];
    int *t = apricot[0][0];

    printf("r: %p, t: %p\n", r, t);

    ++r;
    ++t;
    printf("r: %p, t: %p\n", r, t);

    return 0;
}
