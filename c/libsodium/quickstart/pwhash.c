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

    return 0;
}
