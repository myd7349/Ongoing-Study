#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_search.h"


int cmpi(const void *x, const void *y)
{
    int xx, yy;

    assert(x && y);

    xx = *(int *)x;
    yy = *(int *)y;

    return CMP(xx, yy);
}


int main()
{
    int a[] = { 2, 7, -1, 3, 0, 9 };
    int b = 2;

    int *res;

    qsort(ARRAY(a), sizeof(a[0]), cmpi);
    printvi(ARRAY(a));

    res = binary_search(a, &b, ARRAYSIZE(a), sizeof(a[0]), cmpi);

    if (res != NULL)
        printf("Found %d at %d(%p).\n", b, res - a, res);
    else
        printf("%d doesn't exist.\n", b);

    b = 100;
    res = binary_search(a, &b, ARRAYSIZE(a), sizeof(a[0]), cmpi);

    if (res != NULL)
        printf("Found %d at %d(%p).\n", b, res - a, res);
    else
        printf("%d doesn't exist.\n", b);

    return 0;
}
