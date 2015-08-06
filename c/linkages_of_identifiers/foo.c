#include "zen.h"

#include <stdio.h>

void foo_zen(void)
{
    printf("foo> Zen of life: %d @%p\n", Zen_of_life, &Zen_of_life);
}

void foo_hah(void)
{
    printf("foo> hah: %d @%p\n", hah, &hah);
}

void foo_duang(void)
{
#if TEST_FILE_SCOPE_CONSTANT_LINKAGE
    printf("foo> duang: %d @%p\n", Duang, &Duang);
#endif
}

