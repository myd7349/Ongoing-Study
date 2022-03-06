#include <stdio.h>

#include "GitVersion.h"


#define STR_(x) #x
#define STR(x) STR_(x)


int main(void)
{
    printf(
        "Product version: %s\n"
        "Source version: %s\n"
        "Build version: %s\n",
        STR(PRODUCT_VERSION),
        STR(GIT_VERSION),
        STR(BUILD_VERSION)
    );

    return 0;
}
