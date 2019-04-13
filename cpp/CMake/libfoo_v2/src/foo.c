#include <libfoo/foo.h>

#define STR_IMPL(c) #c
#define STR(c) STR_IMPL(c)

int foo()
{
    return 42;
}

const char *bar()
{
    return STR(FOO_API);
}
