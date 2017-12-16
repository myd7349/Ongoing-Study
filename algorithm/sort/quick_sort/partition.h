// 2017-12-15T16:11+08:00
#ifndef PARTITION_H_
#define PARTITION_H_

/*
From wikipedia:
Partitioning: reorder the array so that all elements with values less than
the pivot come before the pivot, while all elements with values greater than
the pivot come after it (equal values can go either way).
After this partitioning, the pivot is in its final position. This is called
the partition operation.
*/

typedef int partitioni_fn_t(int [], int, int);

int lomuto_partitioni(int arr[], int lb, int ub);

int hoare_partitioni(int arr[], int lb, int ub);

#endif // PARTITION_H_
