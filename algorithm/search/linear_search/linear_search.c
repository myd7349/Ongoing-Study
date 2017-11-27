#include "linear_search.h"

#include <assert.h>
#include <stddef.h>


// Linear searching algorithm using a sentinel described in [1].
int linear_searchi(int x[], unsigned n, int value)
{
    unsigned i = 0;
    int last;

    assert(x != NULL && n > 0);

    // Save x[n - 1] into last and then put value into x[n - 1].
    last = x[n - 1];
    x[n - 1] = value;

    while (x[i] != value)
        ++i;

    // Restore x[n - 1] from last.
    x[n - 1] = last;

    if (i < n - 1 || x[n - 1] == value)
        return i;

    return -1;
}

// References:
// [1] Algorithms Unlocked, Thomas Cormen
