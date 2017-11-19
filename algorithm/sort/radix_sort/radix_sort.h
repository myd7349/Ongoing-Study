// 2017-11-19T11:43+08:00
#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_

int radix_sortu(unsigned *data, unsigned size, unsigned base);

int radix_sorti(int *data, unsigned size, unsigned base);

#define radix_sorti10(data, size) radix_sorti((data), (size), 10)
#define radix_sortu10(data, size) radix_sortu((data), (size), 10)

#endif // RADIX_SORT_H_
