#include "partition.h"

#include <assert.h>
#include <stddef.h>

#include "../../algutils.h"


int lomuto_partitioni(int arr[], int lb, int ub)
{
    int i;
    int j;
    int pivot;

    assert(arr != NULL && lb <= ub);
    if (lb >= ub)
        return -1;

    pivot = arr[ub - 1];

    i = lb - 1;
    for (j = lb; j < ub - 1; ++j)
    {
        if (arr[j] < pivot)
        {
            i++;
            SWAP_T(int, arr[i], arr[j]);
        }
    }

    if (arr[ub - 1] < arr[i + 1])
        SWAP_T(int, arr[i + 1], arr[ub - 1]);

    return i + 1;
}


// Hoare partition scheme
// Note that in Hoare's partition scheme, the pivot's final location is not necessarily
// at the index that was returned, and the next two segments that the main algorithm recurs
// on are (lo..p) and (p+1..hi) as opposed to (lo..p-1) and (p+1..hi) as in Lomuto's scheme.
// In this implementation:
// hoare_partitioni_v0: the pivot's final location is not necessarily at the index that was returned.
// hoare_partitioni: the pivot's final location is at the index that was returned.
#if 0
int hoare_partitioni_v0(int arr[], int lb, int ub)
{
    int pivot;

    assert(arr != NULL && lb <= ub);
    if (lb >= ub)
        return -1;

    pivot = arr[lb];

    lb -= 1;

    while (1)
    {
        do
            lb++;
        while (arr[lb] < pivot);

        do
            ub--;
        while (arr[ub] > pivot);

        if (lb >= ub)
            return ub;

        SWAP_T(int, arr[lb], arr[ub]);
    }

    return -1;
}
#endif


int hoare_partitioni(int arr[], int lb, int ub)
{
    int pivot_pos;
    int pivot;

    assert(arr != NULL && lb <= ub);
    if (lb >= ub)
        return -1;

    pivot_pos = lb;
    pivot = arr[pivot_pos];


    while (lb < ub)
    {
        lb++;
        while (arr[lb] < pivot && lb < ub)
            lb++;

        ub--;
        while (arr[ub] > pivot)
            ub--;

        if (lb < ub)
            SWAP_T(int, arr[lb], arr[ub]);
    }

    SWAP_T(int, arr[pivot_pos], arr[ub]);

    return ub;
}


// References:
// https://en.wikipedia.org/wiki/Quicksort
// Algorithms Unlocked, Thomas Cormen
// C Interfaces and Implementations, David R. Hanson
// https://stackoverflow.com/questions/4177988/how-to-modify-lomuto-partition-scheme
