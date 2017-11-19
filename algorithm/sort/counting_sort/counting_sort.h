// 2017-11-19T12:14+08:00
#ifndef COUNTING_SORT_H_
#define COUNTING_SORT_H_


typedef unsigned key_fn(int);

int counting_sorti(int *data, unsigned size, unsigned k, key_fn key, unsigned *counts, int *output);

int counting_sorti_simple(int *data, unsigned size);

int counting_sortu_simple(unsigned *data, unsigned size);

#endif // COUNTING_SORT_H_
