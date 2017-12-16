// 2017-12-05T10:33+08:00
#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "pivot.h"


void lomuto_partition_quick_sorti(int arr[], int size, pivot_chooser_fn_t choose_pivot);

void hoare_partition_quick_sorti(int arr[], int size, pivot_chooser_fn_t choose_pivot);

#endif // QUICK_SORT_H_
