#include "counting_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../algutils.h"


int counting_sorti(int *data, unsigned size, unsigned k, key_fn key, unsigned *counts, int *output)
{
    unsigned i;
    unsigned total = 0;
    int free_counts = counts == NULL;
    int free_output = output == NULL;

    assert(data != NULL && size > 0);
    assert(k > 0);
    assert(key != NULL);

    if (data == NULL || size == 0 || k == 0 || key == NULL)
        return 1;

#define FREE_COUNTS() do { if (free_counts) free(counts); } while (0)
#define FREE_OUTPUT() do { if (free_output) free(output); } while (0)

    if (output == NULL)
    {
        output = malloc(size * sizeof(int));
        if (output == NULL)
            return 1;

        free_output = 1;
    }

    if (counts == NULL)
    {
        counts = calloc(k, sizeof(unsigned));
        if (counts == NULL)
        {
            FREE_OUTPUT();
            return 1;
        }

        free_counts = 1;
    }
    else
    {
        memset(counts, 0, k * sizeof(unsigned));
    }

    for (i = 0; i < size; ++i)
    {
        unsigned data_key = key(data[i]);
        assert(data_key < k);

        if (data_key >= k)
        {
            FREE_COUNTS();
            FREE_OUTPUT();
            return 1;
        }

        counts[data_key] += 1;
    }

#if 1
    // Stable.
    for (i = 0; i < k; ++i)
    {
        unsigned old_count = counts[i];
        counts[i] = total;
        total += old_count;
    }

    for (i = 0; i < size; ++i)
    {
        output[counts[key(data[i])]] = data[i];
        counts[key(data[i])] += 1;
    }
#else
    // Not stable.
    // If you want to use counting_sort when implementing radix_sort, then
    // you should not use this implementation.
    for (i = 1; i < k; ++i)
        counts[i] = counts[i] + counts[i - 1];

    for (i = 0; i < size; ++i)
    {
        output[counts[key(data[i])] - 1] = data[i];
        counts[key(data[i])] -= 1;
    }
#endif

    memcpy(data, output, size * sizeof(int));

    FREE_COUNTS();
    FREE_OUTPUT();

    return 0;
}


struct keyi_internal
{
    int min;
} _keyi_internal;


unsigned keyi(int num)
{
    return num - _keyi_internal.min;
}


int counting_sorti_simple(int *data, unsigned size)
{
    unsigned k;

    _keyi_internal.min = mini(data, size);
    k = maxi(data, size) - _keyi_internal.min + 1; // might overflow

    return counting_sorti(data, size, k, keyi, NULL, NULL);
}


struct keyu_internal
{
    unsigned min;
} _keyu_internal;


unsigned keyu(int num)
{
    return (unsigned)num - _keyu_internal.min;
}


int counting_sortu_simple(unsigned *data, unsigned size)
{
    unsigned k;

    _keyu_internal.min = minu(data, size);
    k = maxu(data, size) - _keyu_internal.min + 1; // might overflow: (unsigned)-1 - 0 + 1

    return counting_sorti((int *)data, size, k, keyu, NULL, NULL);
}
