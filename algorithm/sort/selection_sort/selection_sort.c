#include "selection_sort.h"

#include <assert.h>
#include <stddef.h>

#include "../../algutils.h"


void selection_sorti(int x[], unsigned n)
{
    unsigned i, j;
    unsigned smallest; // smallest element in the subarray A[i..n].

    assert(x != NULL && n > 0);

    for (i = 0; i + 1 < n; ++i)
    {
        smallest = i;

        for (j = i + 1; j < n; ++j)
        {
            if (x[j] < x[smallest])
                smallest = j;
        }

        if (smallest != i)
            SWAP_T(int, x[i], x[smallest]);
    }
}

// References:
// Algorithms Unlocked, Thomas Cormen
// https://en.wikipedia.org/wiki/Selection_sort
// https://github.com/danlark1/miniselect
