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

void bar_duang(void)
{
#if TEST_FILE_SCOPE_CONSTANT_LINKAGE
    printf("bar> duang: %d @%p\n", Duang, &Duang);
#endif
}
