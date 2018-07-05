#include <stdio.h>

#include "../../algutils.h"
#include "bubble_sort.h"


int main()
{
    int arr[] = { 5, 1, 4, 2, 8 };
    int arr2[] = { 5, 1, 4, 2, 8, -10 };

    bubble_sorti(ARRAY(arr));
    printvinl(ARRAY(arr));

    optimized_bubble_sorti(ARRAY(arr2));
    printvinl(ARRAY(arr2));

    return 0;
}
