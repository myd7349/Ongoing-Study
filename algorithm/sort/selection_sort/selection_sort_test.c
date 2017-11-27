#include <stdio.h>

#include "../../algutils.h"
#include "selection_sort.h"


int main()
{
    int x[] = { 42, -1, 3, 0, 99, 2, 2, 0, 8 };
    selection_sorti(ARRAY(x));
    printvi(ARRAY(x));

    return 0;
}
