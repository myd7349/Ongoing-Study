#include <stdio.h>
#include <stdlib.h>

#include <sodium.h>


int main(void)
{
    int res = sodium_init();
    if (res < 0)
    {
        fprintf(stderr, "sodium_init failed: %d\n", res);
        return EXIT_FAILURE;
    }

    res = sodium_init();
    if (res == 1)
        puts("sodium_init has already been called.");

    return 0;
}
