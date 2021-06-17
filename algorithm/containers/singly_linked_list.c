#include "singly_linked_list.h"

#include <assert.h>
#include <stdlib.h>


struct snode_t
{
    snode_t next;
    void *data;
};


struct slist_t
{
    size_t size;
    snode_t first;
};


slist_t slist_new()
{
    return calloc(1, sizeof(struct slist_t));
}


slist_t slist_copy(slist_t list)
{
    slist_t newlist = slist_new();

    if (list != NULL)
    {
        slist_for_each(list, node)
        {
            slist_push_back(newlist, snode_data(node));
        }
    }

    return newlist;
}


void slist_clear(slist_t list)
{
    assert(list != NULL);

    if (list != NULL)
    {
        for (snode_t node = slist_head(list); node != NULL;)
        {
            snode_t current_node = node;
            node = snode_next(node);
            free(current_node);
        }

        list->first = NULL;
        list->size = 0;
    }
}


void slist_resize(slist_t list, size_t size)
{
    assert(list != NULL);

    if (list->size < size)
    {
        size_t count = size - list->size;

        for (size_t i = 0; i < count; ++i)
            slist_push_back(list, NULL);
    }
    else if (list->size > size)
    {
        if (size == 0)
        {
            slist_clear(list);
        }
        else
        {
            for (snode_t node = slist_at(list, size + 1); node != NULL;)
            {
                snode_t current_node = node;
                node = node->next;
                free(current_node);
            }

            slist_at(list, size)->next = NULL;
            list->size = size;
        }
    }
}


void slist_free(slist_t *list)
{
    assert(list != NULL);

    if (*list != NULL)
    {
        slist_clear(*list);
        FREE(*list);
    }
}


void slist_extend(slist_t list, slist_t list2)
{
    assert(list != NULL);

    if (list2 == NULL)
        return;

    slist_for_each(list2, node)
    {
        slist_push_back(list, node);
    }
}


snode_t slist_head(slist_t list)
{
    assert(list != NULL);
    return list->first;
}


snode_t slist_at(slist_t list, size_t i)
{
    size_t j = 0;

    assert(list != NULL);

    if (i >= list->size)
        return NULL;

    slist_for_each(list, node)
    {
        if (j++ == i)
            return node;
    }

    return NULL;
}


void slist_push_front(slist_t list, void *data)
{
    snode_t node = NULL;

    assert(list != NULL);

    node = malloc(sizeof(struct snode_t));
    node->data = data;
    node->next = list->first;
    list->first = node;

    list->size += 1;
}


void slist_push_back(slist_t list, void *data)
{
    snode_t node = NULL;

    assert(list != NULL);

    node = malloc(sizeof(struct snode_t));
    node->data = data;
    node->next = NULL;

    if (slist_empty(list))
        list->first = node;
    else
        slist_at(list, list->size - 1)->next = node;

    list->size += 1;
}


void slist_pop_front(slist_t list, void **data)
{
    snode_t head = NULL;

    assert(list != NULL);

    if (slist_empty(list))
    {
        if (data != NULL)
            *data = NULL;
        return;
    }

    head = slist_head(list);
    list->first = head->next;
    list->size -= 1;

    if (data != NULL)
        *data = head->data;

    free(head);
}


void slist_pop_back(slist_t list, void **data)
{
    assert(list != NULL);

    if (slist_empty(list))
    {
        if (data != NULL)
            *data = NULL;
        return;
    }

    if (slist_size(list) == 1)
    {
        if (data != NULL)
            *data = list->first->data;
        FREE(list->first);
    }
    else
    {
        snode_t node_before_tail = slist_at(list, list->size - 2);
        snode_t tail = snode_next(node_before_tail);
        node_before_tail->next = NULL;
        if (data != NULL)
            *data = tail->data;
        free(tail);
    }

    list->size -= 1;
}


size_t slist_size(slist_t list)
{
    assert(list != NULL);
    return list->size;
}


snode_t snode_next(snode_t node)
{
    assert(node != NULL);
    return node->next;
}


void *snode_data(snode_t node)
{
    assert(node != NULL);
    return node->data;
}


snode_t slist_find_if(slist_t list, equal_fn_t equal_fn, void *equal_fn_rhs, snode_t pos)
{
    assert(list != NULL);
    assert(equal_fn != NULL);

    if (pos == NULL)
        pos = slist_head(list);

    for (snode_t node = pos; node != NULL; node = snode_next(node))
    {
        if (equal_fn(node, equal_fn_rhs))
            return node;
    }

    return NULL;
}



void slist_reverse(slist_t list)
{
    snode_t prev = NULL;

    assert(list != NULL);

    for (snode_t current = slist_head(list), next = NULL;
         current != NULL;
         prev = current, current = next)
    {
        next = current->next;
        current->next = prev;
    }

    list->first = prev;
}


// References:
// C Interfaces and Implementations, Chapter 7
// https://github.com/zeromq/czmq/blob/master/include/zlist.h
// https://en.wikipedia.org/wiki/Linked_list
// https://github.com/torvalds/linux/blob/master/include/linux/list.h
// https://github.com/torvalds/linux/blob/master/lib/llist.c
// https://github.com/PeterRK/DSGO/blob/master/LinkedList/list/list.go
// https://coolshell.cn/articles/8990.html
// http://wordaligned.org/articles/two-star-programming
// https://www.zhihu.com/question/271003130/answer/361367751
// RtlInitializeSListHead
// https://github.com/tylov/STC/blob/master/include/stc/clist.h
