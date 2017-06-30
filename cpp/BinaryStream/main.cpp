#include <iostream>

#include "SimpleFileDataSource.hpp"
#include "../common.h"
#include "../dividing_lines.h"


int main()
{
    double data[][5] = {
        { 0.1, 0.2, 0.3, 0.4, 0.5 },
        { 1.1, 1.2, 1.3, 1.4, 1.5 },
        { 2.1, 2.2, 2.3, 2.4, 2.5 },
    };

    std::wstring fileName = L"data.dat";

    std::ofstream os(ws2s(fileName));
    if (os.is_open())
    {
        for (size_t j = 0; j < ARRAYSIZE(data[0]); ++j)
        {
            for (size_t i = 0; i < ARRAYSIZE(data); ++i)
                os.write(reinterpret_cast<const char *>(&data[i][j]), sizeof data[i][j]);
        }

        os.close();
    }

    SharedFileDataSourcePtr dataSource = std::make_shared<SimpleFileDataSource<double>>(3, 1);
    Verify(dataSource->ReadFile(fileName));
    for (int i = 0; i < dataSource->GetChannelCount(); ++i)
    {
        for (int j = 0; j < dataSource->GetLength(); ++j)
            std::cout << dataSource->Read(i, j, 1)[0] << "\t";

        std::cout << std::endl;
    }

    DIVIDING_LINE_2('-', 79);

    short data2[][5] = {
        { short(0.1 * 1000), short(0.2 * 1000), short(0.3 * 1000), short(0.4 * 1000), short(0.5 * 1000) },
        { short(1.1 * 1000), short(1.2 * 1000), short(1.3 * 1000), short(1.4 * 1000), short(1.5 * 1000) },
        { short(2.1 * 1000), short(2.2 * 1000), short(2.3 * 1000), short(2.4 * 1000), short(2.5 * 1000) },
    };

    std::ofstream os2(ws2s(fileName));
    if (os2.is_open())
    {
        for (size_t j = 0; j < ARRAYSIZE(data2[0]); ++j)
        {
            for (size_t i = 0; i < ARRAYSIZE(data2); ++i)
                os2.write(reinterpret_cast<const char *>(&data2[i][j]), sizeof data2[i][j]);
        }

        os2.close();
    }

    dataSource = std::make_shared<SimpleFileDataSource<short>>(3, 1);
    Verify(dataSource->ReadFile(fileName));
    for (int i = 0; i < dataSource->GetChannelCount(); ++i)
    {
        for (int j = 0; j < dataSource->GetLength(); ++j)
            std::cout << dataSource->Read(i, j, 1)[0] << "\t";

        std::cout << std::endl;
    }

    return 0;
}
