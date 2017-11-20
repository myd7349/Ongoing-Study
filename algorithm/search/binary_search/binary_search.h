// 2017-11-19T18:02+08:00
#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

#include <stddef.h>

#include "../../algutils.h"

// C:
// <stdlib.h> bsearch, bsearch_s
// C++:
// <algorithm> std::binary_search
void *binary_search(const void *key, const void *ptr, size_t count, size_t size, cmp_fn_t cmp);


#endif // BINARY_SEARCH_H_
