#include <limits.h>

#include "../../algutils.h"
#include "radix_sort.h"


int main()
{
    unsigned a[] = { 0, 3, 1, 4, 2, 5 };
    unsigned b[] = { 0, 3, 1, 4, 2, 5 };
    unsigned c[] = { 257, 0, 65536, 128, 129, 70, UINT_MAX, INT_MAX, CHAR_BIT };
    int d[] = { 257, INT_MIN, 30, 65535, -1, -42, 42 };

    radix_sortu(ARRAY(a), 10);
    printvu(ARRAY(a));

    radix_sortu(ARRAY(b), 2);
    printvu(ARRAY(b));

    radix_sortu(ARRAY(c), 256);
    printvu(ARRAY(c));

    radix_sorti(ARRAY(d), 10);
    printvi(ARRAY(d));

    return 0;
}
