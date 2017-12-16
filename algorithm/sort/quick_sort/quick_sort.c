#include "quick_sort.h"

#include <assert.h>

#ifndef NDEBUG
# include <stdio.h>
# include "../../algutils.h"
#endif

#include "partition.h"


void quick_sorti_impl(int arr[], int lb, int ub, partitioni_fn_t partitioni, pivot_chooser_fn_t choose_pivot, int level)
{
    int pivot;

    assert(arr != NULL && lb >= 0 && lb <= ub && partitioni != NULL);

    if (lb + 1 < ub)
    {
#ifndef NDEBUG
        INDENT4(level);
        printf("Sort: ");
        printvinl(arr + lb, ub - lb);
#endif

        pivot = partitioni(arr, lb, ub, choose_pivot);

#ifndef NDEBUG
        INDENT4(level);
        printf("Partition: ");
        printvi(arr + lb, pivot - lb);
        printf(" [%d] ", arr[pivot]);
        printvinl(arr + pivot + 1, ub - pivot - 1);
#endif

        quick_sorti_impl(arr, lb, pivot, partitioni, choose_pivot, level + 1);
        quick_sorti_impl(arr, pivot + 1, ub, partitioni, choose_pivot, level + 1);
    }
}


void lomuto_partition_quick_sorti(int arr[], int size, pivot_chooser_fn_t choose_pivot)
{
    quick_sorti_impl(arr, 0, size, lomuto_partitioni, choose_pivot, 0);
}


void hoare_partition_quick_sorti(int arr[], int size, pivot_chooser_fn_t choose_pivot)
{
    quick_sorti_impl(arr, 0, size, hoare_partitioni, choose_pivot, 0);
}


// References:
// https://en.wikipedia.org/wiki/Quicksort
// Algorithms Unlocked, Thomas Cormen
// C Interfaces and Implementations, David R. Hanson
