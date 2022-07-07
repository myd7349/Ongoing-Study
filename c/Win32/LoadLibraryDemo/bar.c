#include "bar.h"

#include <stdio.h>

#include "foo.h"


void Bar(void)
{
    Foo();

    puts("Hello from Bar.");    
}
