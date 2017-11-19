#include "counting_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../algutils.h"


int counting_sorti(int *data, unsigned size, unsigned k, key_fn key)
{
    unsigned *counts = NULL;
    int *output = NULL;
    unsigned i;
    unsigned total = 0;

    assert(data != NULL && size > 0);
    assert(k > 0);
    assert(key != NULL);

    if (data == NULL || size == 0 || k == 0 || key == NULL)
        return 1;

    output = malloc(size * sizeof(int));
    counts = calloc(k, sizeof(unsigned));

    if (counts == NULL || output == NULL)
    {
        free(counts);
        free(output);
        return 1;
    }

    for (i = 0; i < size; ++i)
    {
        unsigned data_key = key(data[i]);

        if (data_key >= k)
        {
            free(counts);
            free(output);
            return 1;
        }

        counts[data_key] += 1;
    }

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

    memcpy(data, output, size * sizeof(int));

    free(counts);
    free(output);

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

    return counting_sorti(data, size, k, keyi);
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

    return counting_sorti((int *)data, size, k, keyu);
}
