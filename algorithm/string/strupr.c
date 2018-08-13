#include <assert.h>
#include <ctype.h>
#include <string.h>


char *strupr(char *str)
{
    size_t len;
    size_t i;

    assert(str != NULL);

    len = strlen(str);

    for (i = 0; i < len; ++i)
        str[i] = toupper(str[i]);

    return str;
}
