// 2018-08-08T21:32+08:00
#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>

#include "../algutils.h"


C_API_BEGIN

typedef struct dyarr_t *dyarr_t;

#define INVALID_INDEX ((size_t)~0)

dyarr_t dyarr_new(size_t elem_size, bool zero_terminated, bool delete_data);
dyarr_t dyarr_sized_new(size_t elem_size, size_t size, bool zero_terminated, bool delete_data);
dyarr_t dyarr_wrap(void *data, size_t elem_size, size_t size, bool zero_terminated, bool fixed_size, bool delete_data);
dyarr_t dyarr_copy(dyarr_t arr);
void dyarr_clear(dyarr_t arr);
bool dyarr_resize(dyarr_t arr, size_t size);
bool dyarr_reserve(dyarr_t arr, size_t capacity);
void dyarr_free(dyarr_t *parr);
bool dyarr_extend(dyarr_t arr, dyarr_t arr2);

void *dyarr_data(dyarr_t arr);
void *dyarr_at(dyarr_t arr, size_t i);

bool dyarr_asign(dyarr_t arr, size_t pos, void *data);
bool dyarr_prepend(dyarr_t arr, void *data, size_t size);
bool dyarr_append(dyarr_t arr, void *data, size_t size);
bool dyarr_push_front(dyarr_t arr, void *data);
bool dyarr_pop_front(dyarr_t arr, void *data);
bool dyarr_push_back(dyarr_t arr, void *data);
bool dyarr_pop_back(dyarr_t arr, void *data);
bool dyarr_insert(dyarr_t arr, size_t pos, void *data);
bool dyarr_insert_many(dyarr_t arr, size_t pos, void *data, size_t count);
bool dyarr_remove(dyarr_t arr, size_t pos, void *data);
bool dyarr_remove_many(dyarr_t arr, size_t pos, size_t count, dyarr_t *removed);
size_t dyarr_index(dyarr_t arr, size_t pos, void *data);
size_t dyarr_rindex(dyarr_t arr, size_t pos, void *data);
bool dyarr_reverse(dyarr_t arr);
size_t dyarr_count(dyarr_t arr, void *data);
size_t dyarr_count_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs);
bool dyarr_get_delete_data(dyarr_t arr);
void dyarr_set_delete_data(dyarr_t arr, bool delete_data);

bool dyarr_zero_terminated(dyarr_t arr);
size_t dyarr_elem_size(dyarr_t arr);
size_t dyarr_size(dyarr_t arr);
size_t dyarr_capacity(dyarr_t arr);

size_t dyarr_find_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs, size_t pos);
size_t dyarr_rfind_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs, size_t pos);
void dyarr_sort(dyarr_t arr, cmp_fn_t cmp_fn);
void dyarr_apply(dyarr_t arr, void (*apply_fn)(size_t, void *));

#define dyarr_empty(arr) (dyarr_size((arr)) == 0)
#define dyarr_first(arr) dyarr_at((arr), 0)
#define dyarr_last(arr) (!dyarr_empty((arr)) ? dyarr_at((arr), dyarr_size((arr)) - 1) : NULL)

C_API_END

#endif // DYNAMIC_ARRAY_H_
