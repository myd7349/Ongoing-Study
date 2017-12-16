// 2017-12-15T16:11+08:00
#ifndef PARTITION_H_
#define PARTITION_H_

#include "pivot.h"

/*
From wikipedia:
Partitioning: reorder the array so that all elements with values less than
the pivot come before the pivot, while all elements with values greater than
the pivot come after it (equal values can go either way).
After this partitioning, the pivot is in its final position. This is called
the partition operation.
*/

typedef int partitioni_fn_t(int [], int, int, pivot_chooser_fn_t);

int lomuto_partitioni(int arr[], int lb, int ub, pivot_chooser_fn_t choose_pivot);

int hoare_partitioni(int arr[], int lb, int ub, pivot_chooser_fn_t choose_pivot);

#endif // PARTITION_H_
