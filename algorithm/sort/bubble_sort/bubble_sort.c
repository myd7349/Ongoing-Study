#include "bubble_sort.h"

#include <assert.h>
#include <stddef.h>

#include "../../algutils.h"


void bubble_sorti(int arr[], int n)
{
    int i;
    int swapped;

    assert(arr != NULL);
    assert(n > 0);

    do
    {
        swapped = 0;

        for (i = 1; i < n; ++i)
        {
            if (arr[i - 1] > arr[i])
            {
                SWAP_T(int, arr[i - 1], arr[i]);
                swapped = 1;
            }
        }
    } while (swapped);
}


void optimized_bubble_sorti(int arr[], int n)
{
    int i;
    int new_n;

    assert(arr != NULL);
    assert(n > 0);

    do
    {
        new_n = 0;

        for (i = 1; i < n; ++i)
        {
            if (arr[i - 1] > arr[i])
            {
                SWAP_T(int, arr[i - 1], arr[i]);
                new_n = i;
            }
        }

        n = new_n;
    } while (n != 0);
}


// References:
// https://en.wikipedia.org/wiki/Bubble_sort
