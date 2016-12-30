// 2016-12-30T12:13:31+08:00
#ifndef ALGUTILS_H_
#define ALGUTILS_H_

typedef int (*cmp_fn_t)(const void *, const void *);

void swap(void *p, void *q, unsigned elem_size, void *temp_elem);

#endif // ALGUTILS_H_
