#include "insert_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ELEM_AT(data, elem_size, i) ((char *)(data) + (i) * (elem_size))


int insert_sort_impl(void *data, unsigned size, unsigned elem_size, cmp_fn_t cmp_fn, void *temp_elem)
{
    for (unsigned i = 1; i < size; ++i)
    {
        for (unsigned j = i;
             j > 0 && cmp_fn(ELEM_AT(data, elem_size, j - 1), ELEM_AT(data, elem_size, j)) > 0;
             --j)
            swap(ELEM_AT(data, elem_size, j - 1), ELEM_AT(data, elem_size, j), elem_size, temp_elem);
    }

    return 0;
}

int insert_sort_impl_v2(void *data, unsigned size, unsigned elem_size, cmp_fn_t cmp_fn, void *temp_elem)
{
    for (unsigned i = 1; i < size; ++i)
    {
        memcpy(temp_elem, ELEM_AT(data, elem_size, i), elem_size);

        unsigned j = i - 1;
        for (; j + 1 > 0 && cmp_fn(ELEM_AT(data, elem_size, j), temp_elem) > 0; --j)
            memcpy(ELEM_AT(data, elem_size, j + 1), ELEM_AT(data, elem_size, j), elem_size);

        memcpy(ELEM_AT(data, elem_size, j + 1), temp_elem, elem_size);
    }

    return 0;
}


int insert_sort(void *data, unsigned size, unsigned elem_size, cmp_fn_t cmp_fn)
{
    assert(data != NULL && size > 0 && elem_size > 0);
    if (data == NULL || size == 0 || elem_size == 0)
        return 1;

    assert(cmp_fn != NULL);
    if (cmp_fn == NULL)
        return 1;

    if (size == 1)
        return 0;

    // temporary element used for swapping two elements
    void *temp_elem = malloc(elem_size);
    if (temp_elem == NULL)
        return 1;

    int res = insert_sort_impl_v2(data, size, elem_size, cmp_fn, temp_elem);

    free(temp_elem);

    return res;
}


void insert_sorti_old_school(int arr[], int n)
{
    int i, j;
    int temp;
    (void)temp;

    assert(arr != NULL && n >= 0);

    for (i = 0; i < n; ++i)
    {
        for (j = n - 1; j > i; --j)
        {
            if (arr[i] > arr[j])
            {
#if 0
                SWAP_T(int, arr[i], arr[j]);
#else
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
#endif
            }
        }
    }
}

// References:
// https://en.wikipedia.org/wiki/Insertion_sort
