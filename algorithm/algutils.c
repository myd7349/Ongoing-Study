#include "algutils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


void swap(void *p, void *q, unsigned elem_size, void *temp_elem)
{
    assert(p != NULL && q != NULL);
    assert(elem_size > 0);
    assert(temp_elem != NULL);

    memcpy(temp_elem, p, elem_size);
    memcpy(p, q, elem_size);
    memcpy(q, temp_elem, elem_size);
}
