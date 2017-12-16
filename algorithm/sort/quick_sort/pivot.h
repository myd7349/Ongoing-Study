// 2017-12-15T18:49+08:00
#ifndef PIVOT_H_
#define PIVOT_H_

typedef int pivot_chooser_fn_t(int [], int, int);

int first(int arr[], int lb, int ub);

int last(int arr[], int lb, int ub);

int middle(int arr[], int lb, int ub);

int middle_of_three(int arr[], int lb, int ub);

int random_chooser(int arr[], int lb, int ub);

#endif // PIVOT_H_
