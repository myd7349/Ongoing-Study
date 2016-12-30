#include "insert_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int insert_sort_impl(void *data, unsigned size, unsigned elem_size, cmp_fn_t cmp_fn, void *temp_elem)
{
    for (unsigned i = 1; i < size; ++i)
    {
        void *curr_elem = (char *)data + i * elem_size;

        unsigned j = 0;
        for (; j < i; ++j)
        {
            void *elem_to_cmp = (char *)data + j * elem_size;
            if (cmp_fn(elem_to_cmp, curr_elem) > 0)
                break;
        }

        if (j < i)
            swap(curr_elem, (char *)data + j * elem_size, elem_size, temp_elem);
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

    int res = insert_sort_impl(data, size, elem_size, cmp_fn, temp_elem);

    free(temp_elem);

    return res;
}
