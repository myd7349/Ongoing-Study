// 2016-12-30T12:20:16+08:00
#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include "../../algutils.h"


int insert_sort(void *elems, unsigned elem_count, unsigned elem_size, cmp_fn_t cmp_fn);

void insert_sorti_old_school(int arr[], int n);


#endif // INSERT_SORT_H
