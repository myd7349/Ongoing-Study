// 2017-11-19T17:17+08:00
#include "../../algutils.h"


int main()
{
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    rotatei(ARRAY(a), -3); // left rotate
    printvinl(ARRAY(a));

    rotatei(ARRAY(a), 3); // right rotate
    printvinl(ARRAY(a));

    rotatei(ARRAY(a), 17);
    printvinl(ARRAY(a));

    rotatei(ARRAY(a), -17);
    printvinl(ARRAY(a));

    rotatei(ARRAY(a), 12);
    printvinl(ARRAY(a));

    return 0;
}
