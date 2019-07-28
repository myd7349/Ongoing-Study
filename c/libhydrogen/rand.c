#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <hydrogen.h>


void setup(void)
{
    if (hydro_init() != 0)
        abort();
}


void test_hydro_random_u32(void)
{
    puts("------------------------------------------------------------");

    for (int i = 0; i < 10; ++i)
        printf("%"PRIu32"\n", hydro_random_u32());
}


void test_hydro_random_uniform(void)
{
    puts("------------------------------------------------------------");

    for (int i = 0; i < 10; ++i)
        printf("%"PRIu32"\n", hydro_random_uniform(10));
}


void test_hydro_random_buf(void)
{
    puts("------------------------------------------------------------");

    uint8_t buf[32];
    char rep[sizeof(buf) * 2 + 1];

    for (int i = 0; i < 10; ++i)
    {
        hydro_random_buf(buf, sizeof buf);
        if (hydro_bin2hex(rep, sizeof rep, buf, sizeof buf) != NULL)
            printf("%s\n", rep);
    }
}


int main(void)
{
    setup();

    test_hydro_random_u32();
    test_hydro_random_uniform();
    test_hydro_random_buf();

    return 0;
}
