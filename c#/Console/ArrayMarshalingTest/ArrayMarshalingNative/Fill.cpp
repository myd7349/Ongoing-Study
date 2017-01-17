#define FILL_API __declspec(dllexport)
#include "Fill.h"

#include <cassert>


void Fill(double array[], size_t len)
{
    assert(array != nullptr);

    for (size_t i = 0; i < len; ++i)
        array[i] = i;
}