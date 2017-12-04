#include "merge.h"

#include <assert.h>
#include <string.h>


void merge2i(const int *x, int m, const int *y, int n, int output[])
{
    int i = 0;
    int j = 0;

    assert(x != NULL && m >= 0);
    assert(y != NULL && n >= 0);
    assert(output != NULL && output != x && output != y);

    while (i < m)
    {
        if (j == n)
        {
            memcpy(output, x + i, (m - i) * sizeof(int));
            return;
        }

        if (y[j] < x[i])
            *output = y[j++];
        else
            *output = x[i++];

        ++output;
    }

    memcpy(output, y + j, (n - j) * sizeof(int));
}


void mergei(int arr[], int lb, int mid, int ub, int output[])
{
    merge2i(arr + lb, mid - lb, arr + mid, ub - mid, output);
}


// References:
// cppreference:merge
