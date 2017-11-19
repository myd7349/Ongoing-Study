#include "radix_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../algutils.h"
#include "../counting_sort/counting_sort.h"


unsigned get_digits_count(unsigned num, unsigned base)
{
    unsigned digits_count = 1;

    assert(base > 1);
    if (base <= 1)
        return 0;

    while (num >= base)
    {
        num /= base;
        digits_count += 1;
    }

    return digits_count;
}


struct radix_sortu_internal
{
    unsigned base;
    unsigned radix;
} _radix_sortu_internal;


unsigned radix_key(int num)
{
    return (unsigned)num / _radix_sortu_internal.radix % _radix_sortu_internal.base;
}


int radix_sortu(unsigned *data, unsigned size, unsigned base)
{
    unsigned digits;
    unsigned i;

    unsigned *counts = NULL;
    unsigned *output = NULL;

    assert(data != NULL && size > 0);
    assert(base > 1 && base <= 256);

    if (data == NULL || size == 0)
        return 1;

    if (base <= 1)
        return 1;

    digits = get_digits_count(maxu(data, size), base);
    if (digits == 0)
        return 1;

    if ((counts = calloc(base, sizeof(unsigned))) == NULL ||
        (output = malloc(size * sizeof(unsigned))) == NULL)
    {
        free(counts);
        free(output);
        return 1;
    }

    _radix_sortu_internal.base = base;
    _radix_sortu_internal.radix = 1;

    for (i = 1; i <= digits; ++i)
    {
        counting_sorti((int *)data, size, base, radix_key, counts, (int *)output);
        _radix_sortu_internal.radix *= base;
    }

    free(counts);
    free(output);

    return 0;
}


int radix_sorti(int *data, unsigned size, unsigned radix)
{
    unsigned pos;

    int res;
    if ((res = radix_sortu((unsigned *)data, size, radix)) != 0)
        return res;

    for (pos = 0; pos < size; ++pos)
    {
        if (data[pos] < 0)
            break;
    }

    if (pos < size)
        rotatei(data, size, size - pos);

    return 0;
}

// References:
// https://stackoverflow.com/questions/15306665/radix-sort-for-negative-integers
