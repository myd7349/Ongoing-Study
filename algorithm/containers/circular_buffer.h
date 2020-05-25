#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

#include "../algutils.h"

C_API_BEGIN

#define CIRCBUF_INVALID_INDEX ((size_t)~0)
#define CIRCBUF_INVALID_SIZE  ((size_t)~0)

typedef struct circbuf_impl_t *circbuf_t;

circbuf_t circbuf_new(size_t capacity, size_t elem_size);
void circbuf_free(circbuf_t *pbuf);

bool circbuf_is_valid(circbuf_t buf);
size_t circbuf_capacity(circbuf_t buf);
size_t circbuf_size(circbuf_t buf);
size_t circbuf_reserve(circbuf_t buf);
size_t circbuf_elem_size(circbuf_t buf);
size_t circbuf_head(circbuf_t buf);
size_t circbuf_tail(circbuf_t buf);

void circbuf_linearize(circbuf_t buf);
bool circbuf_is_linearized(circbuf_t buf);

void *circbuf_data(circbuf_t buf);
void *circbuf_array_one(circbuf_t buf);
void *circbuf_array_two(circbuf_t buf);

void *circbuf_at(circbuf_t buf, size_t pos);
bool circbuf_assign(circbuf_t buf, size_t pos, void *data);

void circbuf_rotate(circbuf_t buf, size_t new_begin);

size_t circbuf_resize(circbuf_t buf, size_t new_size);
size_t circbuf_rresize(circbuf_t buf, size_t new_size);
size_t circbuf_set_capacity(circbuf_t buf, size_t new_capacity);
size_t circbuf_rset_capacity(circbuf_t buf, size_t new_capacity);

bool circbuf_push_back(circbuf_t buf, void *elem);
bool circbuf_push_front(circbuf_t buf, void *elem);
bool circbuf_pop_back(circbuf_t buf, void *elem);
bool circbuf_pop_front(circbuf_t buf, void *elem);
bool circbuf_insert(circbuf_t buf, size_t pos, void *elem, size_t count);
bool circbuf_rinsert(circbuf_t buf, size_t pos, void *elem, size_t count);
bool circbuf_erase(circbuf_t buf, size_t pos, size_t count, void *elems);
bool circbuf_rerase(circbuf_t buf, size_t pos, size_t count, void *elems);
bool circbuf_clear(circbuf_t buf);

#define circbuf_empty(buf) (circbuf_size((buf)) == 0)
#define circbuf_full(buf)  (circbuf_size((buf)) == circbuf_capacity((buf)))

C_API_END

#endif // CIRCULAR_BUFFER_H_
