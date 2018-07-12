#include <iomanip>
#include <iostream>

#include "../../algutils.h"
#include "humanize.h"


int main()
{
    std::int64_t sizes[] =
    {
        0,
        27,
        999,
        1000,
        1023,
        1024,
        1728,
        110592,
        7077888,
        452984832,
        1024LL * 1024 * 1024 * 2,
        28991029248LL,
        1855425871872LL,
        9223372036854775807LL,
    };

    std::cout << std::setw(20) << "Bytes"
              << std::setw(16) << "SI"
              << std::setw(16) << "BINARY"
              << std::endl;

    for (std::size_t i = 0; i < ARRAYSIZE(sizes); ++i)
    {
        std::cout << std::setw(20) << sizes[i]
                  << std::setw(16) << GetReadableFileSize(sizes[i], true, 3)
                  << std::setw(16) << GetReadableFileSize(sizes[i], false, 4)
                  << std::endl;
    }

    return 0;
}
