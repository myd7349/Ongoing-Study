#include "merge.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
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
    merge2i(arr + lb, mid - lb, arr + mid, ub - mid, output + lb);
}


// See [2]
int mergei_v2(int arr[], int lb, int mid, int ub)
{
    int m = mid - lb + 1;
    int n = ub - mid + 1;
    int *left = NULL;
    int *right = NULL;
    int i = 0;
    int j = 0;
    int k;

    assert(arr != NULL && lb <= mid && mid <= ub);

    left = malloc(m * sizeof(int));
    right = malloc(n * sizeof(int));

    if (left == NULL || right == NULL)
    {
        free(left);
        free(right);
        return 1;
    }

    memcpy(left, arr + lb, (m - 1) * sizeof(int));
    memcpy(right, arr + mid, (n - 1) * sizeof(int));

    left[m - 1] = right[n - 1] = INT_MAX; // sentinel

    for (k = lb; k < ub; ++k)
    {
        if (left[i] < right[j])
            arr[k] = left[i++];
        else if (right[j] < left[i])
            arr[k] = right[j++];
    }

    free(left);
    free(right);

    return 0;
}


// References:
// [1] cppreference:merge
// [2] Algorithms Unlocked, Thomas Cormen
