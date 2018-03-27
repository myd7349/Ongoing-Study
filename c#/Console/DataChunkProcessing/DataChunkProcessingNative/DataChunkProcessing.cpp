#define DATACHUNK_API __declspec(dllexport)
#include "DataChunkProcessing.h"

#include <cassert>
#include <cstdio>


void ProcessDataChunk(double array[], size_t len)
{
    assert(array != nullptr);

    std::putchar('[');

    if (len > 0)
        std::printf("%.0f", array[0]);

    for (size_t i = 1; i < len; ++i)
        std::printf(", %.0f", array[i]);

    std::puts("]");
}
