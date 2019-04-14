#include <libfoo/foo.h>

#define STR_IMPL(c) #c
#define STR(c) STR_IMPL(c)

int foo()
{
    return 42;
}

const char *bar()
{
#ifdef FOO_STATIC_LIB
    return "";
#else
    return STR(FOO_API);
#endif
}
