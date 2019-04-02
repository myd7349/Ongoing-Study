#include <assert.h>
#include <stdlib.h>

#include <foo/foo.h>


int main(void)
{
    assert(foo() == 42);

    if (foo() == 42)
        return 0;
    else
        return EXIT_FAILURE;
}
