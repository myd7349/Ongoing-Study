// 2018-03-01T14:51+08:00
#include <assert.h>
#include <string.h>


const char *reverse(char *str)
{
    char *p = str;
    char *q;

    assert(str != NULL);

    q = str + strlen(str) - 1;

    while (p < q)
    {
        char ch = *p;
        *p++ = *q;
        *q-- = ch;
    }

    return str;
}


// References:
// http://en.cppreference.com/w/c/numeric/math/div
