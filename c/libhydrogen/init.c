#include <stdio.h>
#include <stdlib.h>

#include <hydrogen.h>


void setup(void)
{
    if (hydro_init() != 0)
        abort();
}


int main(void)
{
    setup();

    puts("Hello, libhydrogen!");

    return 0;
}
