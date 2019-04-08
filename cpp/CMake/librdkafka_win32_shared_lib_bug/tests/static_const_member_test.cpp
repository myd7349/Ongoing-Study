#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <foo/foo.h>


int main(void)
{
    assert(Foo::BAR == 42);

    if (Foo::BAR == 42)
        return 0;
    else
        return EXIT_FAILURE;
}
