// 2017-01-07T11:48+08:00
#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include "../algutils.h"

C_API_BEGIN

typedef struct snode_t *snode_t;
typedef struct slist_t *slist_t;

slist_t slist_new();
slist_t slist_copy(slist_t list);
void slist_clear(slist_t list);
void slist_resize(slist_t list, size_t size);
void slist_free(slist_t *list);
void slist_extend(slist_t list, slist_t list2);

snode_t slist_head(slist_t list);
snode_t slist_at(slist_t list, size_t i);

void slist_push_front(slist_t list, void *data);
void slist_push_back(slist_t list, void *data);
void slist_pop_front(slist_t list, void **data);
void slist_pop_back(slist_t list, void **data);

size_t slist_size(slist_t list);

snode_t snode_next(snode_t node);
void *snode_data(snode_t node);

snode_t slist_find_if(slist_t list, equal_fn_t equal_fn, void *equal_fn_rhs, snode_t pos);

void slist_reverse(slist_t list);

//void slist_insert_at(slist_t list, size_t i, void *data);
//void slist_remove_at(slist_t list, size_t i, void **data);
//void slist_reverse
//void slist_new_ex(void *x0, ...)

#define slist_empty(list) (slist_size((list)) == 0)
#define slist_tail(list) (slist_empty(list) ? NULL : slist_at((list), slist_size((list)) - 1))
#define slist_for_each(list, node) for(snode_t node = slist_head(list); node != NULL; node = snode_next(node))

C_API_END

#endif // SINGLY_LINKED_LIST_H_
