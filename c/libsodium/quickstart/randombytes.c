#include <inttypes.h>
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

    for (int i = 0; i < 10; ++i)
        printf("%"PRIu32"\n", randombytes_random());

    for (int i = 0; i < 10; ++i)
        printf("%"PRIu32"\n", randombytes_uniform(10));

    return 0;
}
