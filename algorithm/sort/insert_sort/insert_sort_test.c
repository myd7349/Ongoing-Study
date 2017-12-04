// 2016-12-30T12:03:35+08:00
#include <assert.h>
#include <stdio.h>

#include "../../algutils.h"
#include "insert_sort.h"


int cmp_int(const void *x, const void *y)
{
    assert(x != NULL && y != NULL);
    return *(const int *)x - *(const int *)y;
}


int main(void)
{
    int arr[] = { 5, 1, 3, 0, 2, -1, 42, 20 };

    int res = insert_sort(ARRAY(arr), sizeof(arr[0]), cmp_int);
    assert(res == 0);

    printvinl(ARRAY(arr));

    return 0;
}
