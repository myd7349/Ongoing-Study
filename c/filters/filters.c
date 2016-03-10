// 2016-03-10T13:15+08:00
// 1. cpp filters.c
// 2. gcc -E filters.c
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// HP: High Pass
// LP: Low Pass

typedef enum {
    FM_HP = 0xA,
    FM_LP = 0xB,
} FilterMask;

typedef struct {
    FilterMask mask;
    int        hz;
    double     in[3];
    double     out[3];
} HPFilter, *PHPFilter;

typedef struct {
    FilterMask mask;
    int        hz;
    double     in[6];
    double     out[6];
} LPFilter, *PLPFilter;

typedef void *HPHandle;
typedef void *LPHandle;

#define IS_FILTER_(h, t) ((h) != 0 && ((P##t##Filter)(h))->mask == FM_##t)
#define IS_HP_FILTER(h) IS_FILTER_(h, HP)
#define IS_LP_FILTER(h) IS_FILTER_(h, LP)

#if 1
HPHandle HPFilterInit(int hz)
{
    PHPFilter handle = (PHPFilter)malloc(sizeof(HPFilter));
    if (0 == handle)
        return 0;

    handle->mask = FM_HP;
    handle->hz = hz;

    memset(handle->in, 0, sizeof(handle->in));
    memset(handle->out, 0, sizeof(handle->out));

    return handle;
}

void HPFilterFree(HPHandle handle)
{
    assert(IS_HP_FILTER(handle));
    if (!IS_HP_FILTER(handle))
        return;

    free(handle);
}

LPHandle LPFilterInit(int hz)
{
    PLPFilter handle = (PLPFilter)malloc(sizeof(LPFilter));
    if (0 == handle)
        return 0;

    handle->mask = FM_LP;
    handle->hz = hz;

    memset(handle->in, 0, sizeof(handle->in));
    memset(handle->out, 0, sizeof(handle->out));

    return handle;
}

void LPFilterFree(LPHandle handle)
{
    assert(IS_LP_FILTER(handle));
    if (!IS_LP_FILTER(handle))
        return;

    free(handle);
}
#else
#define FILTER_INIT_DEF(t) \
t##Handle t##FilterInit(int hz)\
{\
    P##t##Filter handle = (P##t##Filter)malloc(sizeof(t##Filter));\
    if (0 == handle)\
        return 0;\
\
    handle->mask = FM_##t;\
    handle->hz = hz;\
\
    memset(handle->in, 0, sizeof(handle->in));\
    memset(handle->out, 0, sizeof(handle->out));\
\
    return handle;\
}

#define FILTER_FREE_DEF(t) \
void t##FilterFree(t##Handle handle)\
{\
    assert(IS_##t##_FILTER(handle));\
    if (!IS_##t##_FILTER(handle))\
        return;\
\
    free(handle);\
}

FILTER_INIT_DEF(HP)

FILTER_FREE_DEF(HP)

FILTER_INIT_DEF(LP)

FILTER_FREE_DEF(LP)

#endif

int main()
{
    return 0;
}
