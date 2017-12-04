#include "../../algutils.h"
#include "counting_sort.h"


int main()
{
    int a[] = { 4, 3, 2, 1 };
    int b[] = { 0, 4, 1, 3, 1, 2, 4, 1 };
    int c[] = { 0, -1, 4, 0, 2, -3, 8 };
    //unsigned d[] = { -1, -2, -3, 0 };
    unsigned d[] = { 1, 2, 3, 0 };

    counting_sorti_simple(ARRAY(a));
    printvinl(ARRAY(a));

    counting_sorti_simple(ARRAY(b));
    printvinl(ARRAY(b));

    counting_sorti_simple(ARRAY(c));
    printvinl(ARRAY(c));

    counting_sortu_simple(ARRAY(d));
    printvunl(ARRAY(d));

    return 0;
}
