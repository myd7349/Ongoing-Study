#include <stdio.h>

#include <cpuinfo.h>


int main(void)
{
    cpuinfo_initialize();
    
    printf("Running on %s CPU\n", cpuinfo_get_package(0)->name);
    printf("Size of level 1 data cache on the fastest core: %u\n",
        cpuinfo_get_processor(0)->cache.l1d->size);
    
    return 0;
}
