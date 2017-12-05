#include "../../algutils.h"
#include "merge.h"
#include "merge_sort.h"


int main()
{
    int arr[] = { 3, 4, 5, -1, 0, 1 };
    int arr2[] = { 5, 4, 3, 1, 0, -1 };
    int arr3[] = { 5, 4, 3, 1, 0, -1, 99, 72, 42, 2 };
    int output[ARRAYSIZE(arr)];

    int a[] = { 3, 4, 5, 6 };
    int b[] = { 2, 3, 7, 9 };
    int result[ARRAYSIZE(a) + ARRAYSIZE(b)];

    mergei(arr, 0, ARRAYSIZE(arr) / 2, ARRAYSIZE(arr), output);
    printvinl(ARRAY(output));

    merge2i(ARRAY(a), ARRAY(b), result);
    printvinl(ARRAY(result));

    merge2i(ARRAY(a), b, 0, result);
    printvinl(result, ARRAYSIZE(a));

    merge2i(a, 0, ARRAY(b), result);
    printvinl(result, ARRAYSIZE(b));

    simple_top_down_merge_sorti(ARRAY(arr2));
    printvinl(ARRAY(arr2));

    mergei_v2(arr, 0, ARRAYSIZE(arr) / 2, ARRAYSIZE(arr));
    printvinl(ARRAY(arr));

    simple_top_down_merge_sorti_v2(ARRAY(arr3));
    printvinl(ARRAY(arr3));

    return 0;
}
