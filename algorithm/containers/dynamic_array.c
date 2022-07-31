#include "dynamic_array.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define DYARR_TYPEID (0xFEFDFCFB)


struct dyarr_t
{
    unsigned magic;
    size_t fixed_size;
    size_t elem_size;
    size_t size;
    size_t capacity;
    bool zero_terminated;
    bool delete_data;
    unsigned char *data;
};


// https://www.zhihu.com/question/36538542/answer/67994276
// https://github.com/facebook/folly/blob/master/folly/FBVector.h
// https://github.com/facebook/folly/blob/master/folly/docs/FBVector.md
// https://github.com/facebook/folly/blob/7f721452a97937211d138f8553ae36192428e4f1/folly/FBVector.h#L1186
// https://github.com/facebook/folly/blob/7f721452a97937211d138f8553ae36192428e4f1/folly/memory/Malloc.h#L220
// C++ Primer, 5th Edition, 9.4. How a vector Grows
static size_t FBVector_growing_policy(size_t capacity, size_t elem_size)
{
    size_t jemallocMinInPlaceExpandable = 4096;

    assert(elem_size > 0);

    if (capacity == 0)
        return MAX(64 / elem_size, 1);

    if (capacity < jemallocMinInPlaceExpandable / elem_size)
        return capacity * 2;

    if (capacity > 4096 * 32 / elem_size)
        return capacity * 2;

    return (capacity * 3 + 1) / 2;
}


// https://github.com/Tencent/rapidjson/blob/73063f5002612c6bf64fe24f851cd5cc0d83eef9/include/rapidjson/document.h#L1289
static size_t RapidJson_growing_policy(size_t capacity, size_t elem_size)
{
    size_t kDefaultObjectCapacity = 16;

    assert(elem_size > 0);

    return capacity = 0 ? kDefaultObjectCapacity : (capacity + (capacity + 1) / 2);
}


// https://github.com/GNOME/glib/blob/3693bc52ad7e9402bd46bcf19e2acdf699102382/glib/garray.c#L792
static size_t GArray_growing_policy(size_t capacity, size_t elem_size)
{
    size_t new_capacity = 1;

    assert(elem_size > 0);

    while (new_capacity < capacity && new_capacity > 0)
        new_capacity <<= 1;

    return new_capacity ? new_capacity : capacity;
}


static size_t calc_new_capacity(size_t capacity, size_t elem_size)
{
    return RapidJson_growing_policy(capacity, elem_size);
}


static bool is_dyarr(dyarr_t arr)
{
    return arr != NULL && arr->magic == DYARR_TYPEID && arr->elem_size > 0;
}


static size_t calc_real_size(size_t new_size, bool zero_terminated)
{
    return new_size + (zero_terminated ? 1 : 0);
}


static size_t dyarr_real_size(dyarr_t arr)
{
    return calc_real_size(dyarr_size(arr), dyarr_zero_terminated(arr));
}


static void dyarr_free_impl(dyarr_t *parr, bool delete_data)
{
    assert(parr != NULL && is_dyarr(*parr));

    if (delete_data)
        free((*parr)->data);
    free(*parr);
    *parr = NULL;
}


static bool dyarr_enlarge_(dyarr_t arr, size_t amount)
{
    if (!is_dyarr(arr))
        return false;

    return dyarr_resize(arr, arr->size + amount);
}


#define ELEM_PTR(arr, i) ((arr)->data + (arr)->elem_size * i)


dyarr_t dyarr_new(size_t elem_size, bool zero_terminated, bool delete_data)
{
    return dyarr_sized_new(elem_size, 0, zero_terminated, delete_data);
}


dyarr_t dyarr_sized_new(size_t elem_size, size_t size, bool zero_terminated, bool delete_data)
{
    dyarr_t arr;

    assert(elem_size > 0);

    arr = calloc(1, sizeof(struct dyarr_t));
    if (arr == NULL)
        return NULL;

    arr->magic = DYARR_TYPEID;
    arr->fixed_size = false;
    arr->elem_size = elem_size;
    arr->zero_terminated = zero_terminated;
    arr->delete_data = delete_data;

    if (!dyarr_resize(arr, size))
    {
        dyarr_free(&arr);
        return NULL;
    }

    return arr;
}


dyarr_t dyarr_wrap(void *data, size_t elem_size, size_t size, bool zero_terminated, bool fixed_size, bool delete_data)
{
    dyarr_t arr;

    assert(data != NULL && size > 0);
    assert(elem_size > 0);

    arr = calloc(1, sizeof(struct dyarr_t));
    if (arr == NULL)
        return NULL;

    arr->magic = DYARR_TYPEID;
    arr->fixed_size = fixed_size;
    arr->elem_size = elem_size;
    arr->size = size;
    arr->capacity = calc_real_size(size, zero_terminated);
    arr->data = data;
    arr->zero_terminated = zero_terminated;
    arr->delete_data = delete_data;
    
    return arr;
}


dyarr_t dyarr_copy(dyarr_t arr)
{
    dyarr_t copy;

    if (arr == NULL)
        return NULL;

    assert(is_dyarr(arr));

    copy = calloc(1, sizeof(struct dyarr_t));
    if (copy == NULL)
        return NULL;

    copy->magic = DYARR_TYPEID;
    copy->elem_size = arr->elem_size;
    copy->zero_terminated = arr->zero_terminated;
    copy->delete_data = true;

    if (!dyarr_reserve(copy, arr->capacity))
    {
        dyarr_free(&copy);
        return NULL;
    }

    memcpy(copy->data, arr->data, arr->elem_size * arr->size);
    return copy;
}


void dyarr_clear(dyarr_t arr)
{
    dyarr_resize(arr, 0);
}


bool dyarr_resize(dyarr_t arr, size_t size)
{
    size_t real_size;

    if (!is_dyarr(arr))
        return false;

    real_size = calc_real_size(size, arr->zero_terminated);
    if (arr->capacity < real_size)
    {
        if (!dyarr_reserve(arr, real_size))
            return false;
    }

    arr->size = size;
    return true;
}


bool dyarr_reserve(dyarr_t arr, size_t capacity)
{
    void *buffer;

    if (!is_dyarr(arr))
        return false;

    if (arr->fixed_size)
        return false;

    if (capacity < dyarr_real_size(arr))
        return false;

    buffer = realloc(arr->data, capacity * arr->elem_size);
    if (buffer != NULL)
    {
        arr->data = buffer;
        if (capacity > arr->capacity)
            memset(ELEM_PTR(arr, arr->capacity), 0, (capacity - arr->capacity) * arr->elem_size);
        arr->capacity = capacity;
        return true;
    }
    
    return false;
}


void dyarr_free(dyarr_t *parr)
{
    if (parr == NULL)
        return;

    assert(is_dyarr(*parr));

    dyarr_free_impl(parr, (*parr)->delete_data);
}


bool dyarr_extend(dyarr_t arr, dyarr_t arr2)
{
    if (!is_dyarr(arr2))
        return false;

    if (dyarr_empty(arr2))
        return true;

    return dyarr_append(arr, arr2->data, arr2->size);
}


void *dyarr_data(dyarr_t arr)
{
    if (!is_dyarr(arr))
        return NULL;

    return arr->data;
}


void *dyarr_at(dyarr_t arr, size_t i)
{
    if (!is_dyarr(arr))
        return NULL;

    if (i > arr->size || (i == arr->size && !arr->zero_terminated))
        return NULL;

    return ELEM_PTR(arr, i);
}


bool dyarr_asign(dyarr_t arr, size_t pos, void *data)
{
    if (!is_dyarr(arr))
        return false;

    if (pos >= arr->size)
        return false;

    assert(data != NULL);
    memcpy(ELEM_PTR(arr, pos), data, arr->elem_size);
    return true;
}


bool dyarr_prepend(dyarr_t arr, void *data, size_t size)
{
    size_t old_size;

    if (!is_dyarr(arr))
        return false;

    assert(data != NULL && size > 0);
    old_size = arr->size;
    if (!dyarr_resize(arr, arr->size + size))
        return false;

    memmove(ELEM_PTR(arr, size), arr->data, old_size * arr->elem_size);
    memcpy(arr->data, data, size * arr->elem_size);
    return true;
}


bool dyarr_append(dyarr_t arr, void *data, size_t size)
{
    size_t old_size;

    if (!is_dyarr(arr))
        return false;

    assert(data != NULL && size > 0);
    old_size = arr->size;
    if (!dyarr_resize(arr, arr->size + size))
        return false;

    memcpy(ELEM_PTR(arr, old_size), data, size * arr->elem_size);
    return true;
}


bool dyarr_push_front(dyarr_t arr, void *data)
{
    return dyarr_prepend(arr, data, 1);
}


bool dyarr_pop_front(dyarr_t arr, void *data)
{
    if (!is_dyarr(arr))
        return false;

    if (dyarr_empty(arr))
        return false;

    if (data != NULL)
        memcpy(data, arr->data, arr->elem_size);

    memmove(arr->data, ELEM_PTR(arr, 1), arr->elem_size);
    arr->size -= 1;

    return true;
}


bool dyarr_push_back(dyarr_t arr, void *data)
{
    return dyarr_append(arr, data, 1);
}


bool dyarr_pop_back(dyarr_t arr, void *data)
{
    if (!is_dyarr(arr))
        return false;

    if (dyarr_empty(arr))
        return false;

    if (data != NULL)
        memcpy(data, dyarr_last(arr), arr->elem_size);

    arr->size -= 1;

    return true;
}


bool dyarr_insert(dyarr_t arr, size_t pos, void *data)
{
    return dyarr_insert_many(arr, pos, data, 1);
}


bool dyarr_insert_many(dyarr_t arr, size_t pos, void *data, size_t count)
{
    size_t old_size;

    if (!is_dyarr(arr))
        return false;

    if (pos > dyarr_size(arr))
        return false;

    assert(data != NULL && count > 0);
    old_size = arr->size;

    if (!dyarr_enlarge_(arr, count))
        return false;

    memcpy(ELEM_PTR(arr, old_size), data, count * arr->elem_size);
    return true;
}


bool dyarr_remove(dyarr_t arr, size_t pos, void *data)
{
    if (!is_dyarr(arr))
        return false;

    if (pos >= arr->size)
        return false;

    if (data != NULL)
        memcpy(data, ELEM_PTR(arr, pos), arr->elem_size);

    memmove(ELEM_PTR(arr, pos), ELEM_PTR(arr, pos + 1), (arr->size - pos) * arr->elem_size);
    arr->size -= 1;
    return true;
}


bool dyarr_remove_many(dyarr_t arr, size_t pos, size_t count, dyarr_t *removed)
{
    bool move_needed = true;

    if (!is_dyarr(arr))
        return false;

    if (pos >= arr->size)
        return false;

    if (pos + count > arr->size)
    {
        count = arr->size - pos;
        move_needed = false;
    }

    if (removed != NULL)
    {
        *removed = dyarr_sized_new(arr->elem_size, count, arr->zero_terminated, true);
        if (*removed == NULL)
            return false;

        memcpy((*removed)->data, ELEM_PTR(arr, pos), count * arr->elem_size);
    }

    if (move_needed)
        memmove(ELEM_PTR(arr, pos), ELEM_PTR(arr, pos + count), count * arr->elem_size);

    return true;
}


#define DEFINE_COMPARE_FUNC(T) \
static int compare_##T(const T *lhs, const T *rhs) \
{ \
    assert(lhs != NULL && rhs != NULL); \
    return CMP(*lhs, *rhs); \
}


DEFINE_COMPARE_FUNC(uint8_t)
DEFINE_COMPARE_FUNC(uint16_t)
DEFINE_COMPARE_FUNC(uint32_t)
DEFINE_COMPARE_FUNC(uint64_t)


size_t dyarr_index(dyarr_t arr, size_t pos, void *data)
{
    size_t i;

    assert(is_dyarr(arr));
    assert(data != NULL);

    if (pos >= arr->size)
        return INVALID_INDEX;

    switch (arr->elem_size)
    {
    case 1:
    {
        const uint8_t *arr_data = (uint8_t *)arr->data + pos;
        const uint8_t *rhs = data;

        for (i = pos; i < arr->size; ++i)
        {
            if (compare_uint8_t(arr_data + i, rhs) == 0)
                return i;
        }
    }
        break;

    case 2:
    {
        uint16_t *arr_data = (uint16_t *)arr->data + pos;
        uint16_t *rhs = data;

        for (i = pos; i < arr->size; ++i)
        {
            if (compare_uint16_t(arr_data + i, rhs) == 0)
                return i;
        }
    }
        break;

    case 4:
    {
        uint32_t *arr_data = (uint32_t *)arr->data + pos;
        uint32_t *rhs = data;

        for (i = pos; i < arr->size; ++i)
        {
            if (compare_uint32_t(arr_data + i, rhs) == 0)
                return i;
        }
    }
        break;

    case 8:
    {
        uint64_t *arr_data = (uint64_t *)arr->data + pos;
        uint64_t *rhs = data;

        for (i = pos; i < arr->size; ++i)
        {
            if (compare_uint64_t(arr_data + i, rhs) == 0)
                return i;
        }
    }
        break;

    default:
        for (i = pos; i < arr->size; ++i)
        {
            if (memcmp(ELEM_PTR(arr, i), data, arr->elem_size) == 0)
                return i;
        }
        break;
    }

    return INVALID_INDEX;
}


size_t dyarr_rindex(dyarr_t arr, size_t pos, void *data)
{
    size_t i;

    assert(is_dyarr(arr));
    assert(data != NULL);

    if (pos >= arr->size)
        return INVALID_INDEX;

    switch (arr->elem_size)
    {
    case 1:
    {
        uint8_t *arr_data = (uint8_t *)arr->data;
        for (i = 0; i <= pos; ++i)
        {
            if (compare_uint8_t(arr_data + pos - i, data) == 0)
                return pos - i;
        }
    }
    break;

    case 2:
    {
        uint16_t *arr_data = (uint16_t *)arr->data;
        for (i = 0; i <= pos; ++i)
        {
            if (compare_uint16_t(arr_data + pos - i, data) == 0)
                return pos - i;
        }
    }
    break;

    case 4:
    {
        uint32_t *arr_data = (uint32_t *)arr->data;
        for (i = 0; i <= pos; ++i)
        {
            if (compare_uint32_t(arr_data + pos - i, data) == 0)
                return pos - i;
        }
    }
    break;

    case 8:
    {
        uint64_t *arr_data = (uint64_t *)arr->data;
        for (i = 0; i <= pos; ++i)
        {
            if (compare_uint64_t(arr_data + pos - i, data) == 0)
                return pos - i;
        }
    }
    break;

    default:
        for (i = 0; i <= pos; ++i)
        {
            if (memcmp(ELEM_PTR(arr, pos - i), data, arr->elem_size) == 0)
                return pos - i;
        }
        break;
    }

    return INVALID_INDEX;
}


bool dyarr_reverse(dyarr_t arr)
{
    size_t i, j;

    assert(is_dyarr(arr));

    if (arr->size < 2)
        return false;

    i = 0;
    j = arr->size - 1;

    switch (arr->elem_size)
    {
    case 1:
    {
        uint8_t *data = (uint8_t *)arr->data;
        while (i < j)
        {
            SWAP_T(uint8_t, data[i], data[j]);
            i++;
            j--;
        }
    }
        break;

    case 2:
    {
        uint16_t *data = (uint16_t *)arr->data;
        while (i < j)
        {
            SWAP_T(uint16_t, data[i], data[j]);
            i++;
            j--;
        }
    }
        break;

    case 4:
    {
        uint32_t *data = (uint32_t *)arr->data;
        while (i < j)
        {
            SWAP_T(uint32_t, data[i], data[j]);
            i++;
            j--;
        }
    }
        break;

    case 8:
    {
        uint64_t *data = (uint64_t *)arr->data;
        while (i < j)
        {
            SWAP_T(uint64_t, data[i], data[j]);
            i++;
            j--;
        }
    }
        break;

    default:
    {
        uint8_t buffer[256];
        void *temp;
        if (arr->elem_size <= sizeof(buffer))
        {
            temp = buffer;
        }
        else
        {
            temp = malloc(arr->elem_size);
            if (temp == NULL)
                return false;
        }

        while (i < j)
        {
            memcpy(temp, ELEM_PTR(arr, i), arr->elem_size);
            memcpy(ELEM_PTR(arr, i), ELEM_PTR(arr, j), arr->elem_size);
            memcpy(ELEM_PTR(arr, j), temp, arr->elem_size);

            i++;
            j--;
        }

        if (temp != buffer)
            free(temp);
    }
        break;
    }

    return true;
}


size_t dyarr_count(dyarr_t arr, void *data)
{
    size_t count = 0;
    size_t pos = 0;

    while ((pos = dyarr_index(arr, pos, data)) != INVALID_INDEX)
    {
        pos += 1;
        count += 1;
    }

    return count;
}


size_t dyarr_count_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs)
{
    size_t i;
    size_t count = 0;

    assert(is_dyarr(arr));
    assert(equal_fn != NULL);

    for (i = 0; i < arr->size; ++i)
    {
        if (equal_fn(ELEM_PTR(arr, i), equal_fn_rhs))
            count += 1;
    }

    return count;
}


bool dyarr_get_delete_data(dyarr_t arr)
{
    assert(is_dyarr(arr));
    return arr->delete_data;
}


void dyarr_set_delete_data(dyarr_t arr, bool delete_data)
{
    assert(is_dyarr(arr));
    arr->delete_data = delete_data;
}


bool dyarr_zero_terminated(dyarr_t arr)
{
    assert(is_dyarr(arr));
    return arr->zero_terminated;
}


size_t dyarr_elem_size(dyarr_t arr)
{
    assert(is_dyarr(arr));
    return arr->elem_size;
}


size_t dyarr_size(dyarr_t arr)
{
    assert(is_dyarr(arr));
    return arr->size;
}


size_t dyarr_capacity(dyarr_t arr)
{
    assert(is_dyarr(arr));
    return arr->capacity;
}


size_t dyarr_find_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs, size_t pos)
{
    size_t i;

    assert(is_dyarr(arr));
    assert(equal_fn != NULL);

    if (pos >= arr->size)
        return INVALID_INDEX;

    for (i = pos; i < arr->size; ++i)
    {
        if (equal_fn(ELEM_PTR(arr, i), equal_fn_rhs))
            return i;
    }

    return INVALID_INDEX;
}


size_t dyarr_rfind_if(dyarr_t arr, equal_fn_t equal_fn, void *equal_fn_rhs, size_t pos)
{
    size_t i;

    assert(is_dyarr(arr));
    assert(equal_fn != NULL);

    if (pos >= arr->size)
        return INVALID_INDEX;

    for (i = 0; i <= pos; ++i)
    {
        if (equal_fn(ELEM_PTR(arr, pos - i), equal_fn_rhs))
            return pos - i;
    }

    return INVALID_INDEX;
}


void dyarr_sort(dyarr_t arr, cmp_fn_t cmp_fn)
{
    assert(is_dyarr(arr));
    if (arr->size < 2)
        return;

    qsort(arr->data, arr->size, arr->elem_size, cmp_fn);
}


void dyarr_apply(dyarr_t arr, void(*apply_fn)(size_t, void *))
{
    size_t i;

    assert(is_dyarr(arr));
    assert(apply_fn != NULL);

    for (i = 0; i < arr->size; ++i)
        apply_fn(i, ELEM_PTR(arr, i));
}


// References:
// https://en.wikipedia.org/wiki/Dynamic_array
// C Interfaces and Implementations, Chapter 10
// https://github.com/drh/cii/blob/master/src/array.c
// https://github.com/torch/tds/blob/master/tds_vec.h
// https://developer.gnome.org/glib/stable/glib-Arrays.html
// https://github.com/GNOME/glib/blob/master/glib/garray.c
// https://www.ibm.com/developerworks/linux/tutorials/l-glib/index.html
// https://opensource.apple.com/source/CF/
// https://en.wikipedia.org/wiki/Core_Foundation
// https://opensource.apple.com/source/CF/CF-855.17/CFArray.h.auto.html
// https://github.com/tboox/tbox/blob/master/src/tbox/container/vector.c
// cprops/vector.h
// https://segmentfault.com/a/1190000007675747
// https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc
// https://stackoverflow.com/questions/16986214/why-type-cast-a-void-pointer
// https://stackoverflow.com/questions/20469958/c-when-is-casting-void-pointer-needed
// https://stackoverflow.com/questions/6380981/c-c-c4047-differs-in-levels-of-indirection-from-int
// https://github.com/caryll/otfcc/blob/master/lib/support/vector-impl.h
// https://github.com/LLNL/zfp
// https://github.com/tylov/STC/blob/master/include/stc/carray.h
// https://github.com/mortie/snow/blob/master/exampleproject/src/vector.c
// https://github.com/eteran/c-vector
// https://github.com/pjreddie/wordle/blob/main/src/vector.c
// https://github.com/glouw/ctl/blob/master/ctl/vec.h
// https://github.com/eteran/c-vector
