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

    assert(arr != NULL && lb >= 0 && lb <= ub && temp != NULL);

#ifndef NDEBUG
    INDENT4(level); printf("Sort: "); printvinl(arr + lb, ub - lb);
#endif

    if (ub - lb < 2)
        return;

    mid = (lb + ub) / 2;

    top_down_merge_sorti_impl(temp, lb, mid, arr, level + 1);
    top_down_merge_sorti_impl(temp, mid, ub, arr, level + 1);

#ifndef NDEBUG
    INDENT4(level); printf("Merge: "); printvi(arr + lb, mid - lb); printf(" + "); printvi(arr + mid, ub - mid);
#endif

    mergei(arr, lb, mid, ub, temp);

#ifndef NDEBUG
    printf(" -> "); printvinl(temp + lb, ub - lb);
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


int simple_top_down_merge_sorti_v2_impl(int arr[], int lb, int ub, int level)
{
    int mid;

    assert(arr != NULL && lb >= 0 && lb <= ub);

#ifndef NDEBUG
    INDENT4(level); printf("Sort: "); printvinl(arr + lb, ub - lb);
#endif

    if (ub - lb < 2)
        return 0;

    mid = (lb + ub) / 2;

    if (simple_top_down_merge_sorti_v2_impl(arr, lb, mid, level + 1) != 0)
        return 1;

    if (simple_top_down_merge_sorti_v2_impl(arr, mid, ub, level + 1) != 0)
        return 1;

#ifndef NDEBUG
    INDENT4(level); printf("Merge: "); printvi(arr + lb, mid - lb); printf(" + "); printvi(arr + mid, ub - mid);
#endif

    if (mergei_v2(arr, lb, mid, ub) != 0)
        return 1;

#ifndef NDEBUG
    printf(" -> "); printvinl(arr + lb, ub - lb);
#endif

    return 0;
}


int simple_top_down_merge_sorti_v2(int arr[], int n)
{
    return simple_top_down_merge_sorti_v2_impl(arr, 0, n, 0);
}


// References:
// Algorithms Unlocked, Thomas Cormen
// https://en.wikipedia.org/wiki/Merge_sort
