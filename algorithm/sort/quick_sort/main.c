#include "../../algutils.h"
#include "quick_sort.h"

#include <stdio.h>
#include <string.h>


int main()
{
    int raw[] = { 5, 4, 3, 1, 0, -1, 99, 72, 42, 2 };
    int raw2[ARRAYSIZE(raw)] = { 1, 2, 3, 4, 4, 6, 7, 8, 9, 10 };
    int arr[ARRAYSIZE(raw)];

    printf("------------ Lomuto partition ------------\n");
    memcpy(arr, raw, sizeof(int) * ARRAYSIZE(arr));
    lomuto_partition_quick_sorti(ARRAY(arr));
    printvinl(ARRAY(arr));

    printf("------------ Hoare partition ------------\n");
    memcpy(arr, raw, sizeof(int) * ARRAYSIZE(arr));
    hoare_partition_quick_sorti(ARRAY(arr));
    printvinl(ARRAY(arr));

    printf("------------ Lomuto partition ------------\n");
    memcpy(arr, raw2, sizeof(int) * ARRAYSIZE(arr));
    lomuto_partition_quick_sorti(ARRAY(arr));
    printvinl(ARRAY(arr));

    printf("------------ Hoare partition ------------\n");
    memcpy(arr, raw2, sizeof(int) * ARRAYSIZE(arr));
    hoare_partition_quick_sorti(ARRAY(arr));
    printvinl(ARRAY(arr));

    return 0;
}
