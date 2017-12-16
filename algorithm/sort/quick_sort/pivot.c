#include "pivot.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "../../algutils.h"


int first(int arr[], int lb, int ub)
{
    assert(arr != NULL && lb <= ub);
    return lb < ub ? lb : -1;
}


int last(int arr[], int lb, int ub)
{
    assert(arr != NULL && lb <= ub);
    return lb < ub ? ub - 1 : -1;
}


int middle(int arr[], int lb, int ub)
{
    assert(arr != NULL && lb <= ub);
    return lb < ub ? (lb + ub - 1) / 2 : -1;
}


int middle_of_three(int arr[], int lb, int ub)
{
    int f, m, l;

    assert(arr != NULL && lb <= ub);
    if (lb + 3 > ub)
        return first(arr, lb, ub);

    f = lb;
    l = ub - 1;
    m = (f + l) / 2;

    if (arr[f] <= arr[m])
    {
        if (arr[m] <= arr[l])
            return m;
        else
            return arr[f] <= arr[l] ? l : f;
    }
    else
    {
        if (arr[l] <= arr[m])
            return m;
        else
            return arr[f] <= arr[l] ? f : l;
    }
}


int random_chooser(int arr[], int lb, int ub)
{
    static int first_shoot = 1;

    assert(arr != NULL && lb <= ub);

    if (lb >= ub)
        return -1;

    if (first_shoot)
    {
        first_shoot = 0;
        srand((unsigned)time(NULL));
    }

    return RANDINT(lb, ub);
}


// References:
// https://en.wikipedia.org/wiki/Quicksort
