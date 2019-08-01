#include <stdio.h>

#define HAVE_PLUGIN


int main(void)
{
#if HAVE_SSL
    puts("SSL enabled!");
#endif

#ifdef HAVE_ZLIB
    puts("ZLIB enabled!");
#endif

// NOT Work!
//#if HAVE_PLUGIN
//    puts("PLUGIN enabled!");
//#endif

    return 0;
}
