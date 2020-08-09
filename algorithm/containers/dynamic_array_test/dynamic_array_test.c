#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "dynamic_array.h"


void print_int32(size_t index, void *x)
{
    assert(x != NULL);
    printf("#%zu: %d\n", index, *(int32_t *)x);
}


void double_int32(size_t index, void *x)
{
    (void)index;
    assert(x != NULL);
    *(int32_t *)x *= 2;
}


void test_dyarr_resize()
{
    dyarr_t arr1 = dyarr_new(1, true, true);
    dyarr_t arr2 = dyarr_new(1, false, true);
    dyarr_t arr3 = dyarr_sized_new(1, 100, true, true);
    bool result;

    assert(dyarr_size(arr1) == 0);
    assert(dyarr_capacity(arr1) > 0);

    result = dyarr_resize(arr1, 10);
    assert(result);
    assert(dyarr_size(arr1) == 10);
    assert(dyarr_capacity(arr1) > 10);

    dyarr_free(&arr1);
    dyarr_free(&arr2);
    dyarr_free(&arr3);
}


void test_dyarr_reserve()
{
    dyarr_t arr = dyarr_new(1, false, true);
    assert(dyarr_capacity(arr) == 0);
    dyarr_reserve(arr, 10);
    assert(dyarr_capacity(arr) == 10);
    dyarr_reserve(arr, 5);
    assert(dyarr_capacity(arr) == 5);
    dyarr_free(&arr);
}


void test_dyarr_find()
{
    int32_t data[] = { 1, 1, 2, 3, 5, 8, 13 };
    int32_t value = 2;

    dyarr_t arr = dyarr_wrap(data, sizeof(data[0]), ARRAYSIZE(data), false, true, false);
    dyarr_apply(arr, double_int32);
    dyarr_apply(arr, print_int32);
    assert(dyarr_index(arr, 0, &value) == 0);
    assert(!dyarr_resize(arr, 10));
    dyarr_free(&arr);
}


void test_dyarr_apply()
{
    dyarr_t arr = dyarr_new(sizeof(int32_t), true, true);
#if 0
    dyarr_push_back(arr, 1);
    dyarr_push_back(arr, 2);
    dyarr_push_back(arr, 3);
    dyarr_push_front(arr, 0);
#else
    int32_t value = 1;
    dyarr_push_back(arr, &value);
    value = 2;
    dyarr_push_back(arr, &value);
    value = 3;
    dyarr_push_back(arr, &value);
    value = 0;
    dyarr_push_front(arr, &value);
#endif

    dyarr_apply(arr, print_int32);
    dyarr_free(&arr);
}


int main()
{
    test_dyarr_resize();
    test_dyarr_reserve();
    test_dyarr_find();
    test_dyarr_apply();

    return 0;
}

// References:
// https://github.com/google/googletest/blob/master/googletest/docs/primer.md
