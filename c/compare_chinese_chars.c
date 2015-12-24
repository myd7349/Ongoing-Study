// 2015-12-24T17:17+08:00
// Marry Christmas Eve!
#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcoll_wrapper(const void *v1, const void *v2)
{
    const char **s1 = (const char **)v1;
    const char **s2 = (const char **)v2;

    assert(v1 != NULL);
    assert(v2 != NULL);

    return strcoll(*s1, *s2);
}

int main(void)
{
    int i = 0;
    const char *names[] = {
        "’‘",
        "«Æ",
        "ÀÔ",
        "¿Ó",
    };

    setlocale(LC_COLLATE, "");

    qsort(names, 4, sizeof(names[0]), strcoll_wrapper);

    for (i = 0; i < sizeof(names)/sizeof(names[0]); i++)
        puts(names[i]);

    return 0;
}

// References:
// https://www.zhihu.com/question/38835930
// http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
