#include <assert.h>
#include <stdio.h>

#include "../singly_linked_list.h"


int main()
{
    slist_t list = slist_new();

    slist_push_back(list, (void *)1);
    slist_push_back(list, (void *)2);
    slist_push_back(list, (void *)3);
    slist_push_back(list, (void *)4);
    slist_push_back(list, (void *)5);
    slist_push_front(list, (void *)6);
    slist_push_front(list, (void *)7);
    slist_push_front(list, (void *)8);
    slist_push_front(list, (void *)9);
    slist_push_front(list, (void *)10);

    printf("List size: %u.\n", slist_size(list));

    slist_for_each(list, node)
    {
        printf("%d\n", (int)snode_data(node));
    }

    void *head;
    slist_pop_front(list, &head);
    assert((int)head == 10);
    assert(slist_size(list) == 9);

    slist_clear(list);
    assert(slist_empty(list));

    slist_free(&list);

    return 0;
}
