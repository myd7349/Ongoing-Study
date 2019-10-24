#ifndef STACK_H_
#define STACK_H_

#include <assert.h>
#include <stddef.h>

#include "error.h"


#define stack_init(type, name, capacity) \
    static type name[capacity]; \
    static int name##_stack_top = -1

#define stack_count(name) (name##_stack_top + 1)

#define stack_capacity(name) (sizeof(name) / sizeof(name[0]))

#define stack_is_empty(name) (name##_stack_top == -1)

#define stack_is_full(name) (name##_stack_top == stack_capacity(name) - 1)

#define stack_push(name, element) \
    do \
    { \
        if (stack_is_full(name)) \
            error("Cann't not push to a full stack!"); \
        name[++name##_stack_top] = (element); \
    } while (0)

#define stack_pop(name) \
    do \
    { \
        if (stack_is_empty(name)) \
            error("Cann't not pop elements from an empty stack!"); \
        --name##_stack_top; \
    } while (0)

#define stack_at(name, index) \
    ( \
        assert((index) >= 0 && (index) < stack_count(name)), name[index] \
    )

#define stack_top(name) \
    ( \
        assert(!stack_is_empty(name)), name[name##_stack_top] \
    )

#endif /* STACK_H_ */
