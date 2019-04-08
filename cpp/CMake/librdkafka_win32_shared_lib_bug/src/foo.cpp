#include "foo/foo.h"

#include <cstdio>


const int Foo::BAR = 42;

void Foo::hello()
{
    std::puts("Hello, world!");
}


int version = 111;


// References:
// https://stackoverflow.com/questions/1563897/static-constant-string-class-member
// https://stackoverflow.com/questions/14627597/static-data-in-dll
