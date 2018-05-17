#include "NativeLib.h"

#include <stdio.h>


void Foo()
{
#ifdef WIN32
    printf("Hello, x86!\n");
#elif defined(WIN64)
    printf("Hello, x64!\n");
#else
# error Unsupported platform!
#endif
}
