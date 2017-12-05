#include "merge_sort.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifndef NDEBUG
# include <stdio.h>
# include "../../algutils.h"
#endif

#include "merge.h"


void top_down_merge_sorti_impl(int arr[], int lb, int ub, int temp[], int level)
{
    int mid;

#ifndef NDEBUG
    INDENT4(level); printf("Sort: "); printvinl(arr + lb, ub - lb);
#endif

    assert(arr != NULL && lb <= ub && temp != NULL);

    if (ub - lb < 2)
        return;

    mid = (lb + ub) / 2;

    top_down_merge_sorti_impl(temp, lb, mid, arr, level + 1);
    top_down_merge_sorti_impl(temp, mid, ub, arr, level + 1);

#ifndef NDEBUG
    INDENT4(level); printf("Merge: "); printvi(arr + lb, mid - lb); printf(" + "); printvinl(arr + mid, ub - mid);
#endif

    mergei(arr, lb, mid, ub, temp);

#ifndef NDEBUG
    INDENT4(level); printf("After Merge: "); printvinl(temp + lb, ub - lb);
#endif
}


void top_down_merge_sorti(int arr[], int n, int temp[])
{
    memcpy(temp, arr, n * sizeof(int));
    top_down_merge_sorti_impl(temp, 0, n, arr, 0);
}


int simple_top_down_merge_sorti(int arr[], int n)
{
    int *temp;

    assert(arr != NULL && n > 0);

    temp = malloc(n * sizeof(int));
    if (temp == NULL)
        return 1;

    top_down_merge_sorti(arr, n, temp);

    free(temp);

    return 0;
}


// References:
// Algorithms Unlocked, Thomas Cormen
// https://en.wikipedia.org/wiki/Merge_sort
