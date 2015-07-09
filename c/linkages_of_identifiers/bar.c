#include "zen.h"

#include <stdio.h>

void bar_zen(void)
{
    printf("bar> Zen of life: %d @%p\n", Zen_of_life, &Zen_of_life);
}

void bar_hah(void)
{
    printf("bar> hah: %d @%p\n", hah, &hah);
}
