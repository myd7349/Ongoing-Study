#include <iostream>

#include "new_data_format.h"


int main()
{
    const char *fileName = "data.ndf";
    const char *metaFileName = "data.ndf.info";

    {
        NewDataFormat ndf(1024 * 1024 / 2, ndf::NDFMeta_DataWidth_DataWidth16Bits, BigEndian);
        ndf.Dump();

        ndf.SetComment("Hello, world!");

        if (ndf.Save(fileName))
            std::cout << "Saved to " << fileName << '\n';
        else
            std::cout << "Failed to save data to " << fileName << '\n';

        if (ndf.Load(fileName))
            std::cout << "Loaded from " << fileName << '\n';
        else
            std::cout << "Failed to load data from " << fileName << '\n';

        ndf.Dump();

        ndf.SetMetaInfoInSeperatedFile(true);

        if (ndf.Save(fileName, metaFileName))
            std::cout << "Saved to " << fileName << " and " << metaFileName << '\n';
        else
            std::cout << "Failed to save data to " << fileName << " and " << metaFileName << '\n';
    }

    {
        NewDataFormat ndf(fileName, metaFileName);
        ndf.Dump();

        ndf.SetComment("Hello, world 3000 times!");
        ndf.SetData(0, 42);
        ndf.SetData(1, 123);
        ndf.SetData(10, 'F');
        ndf.SetData(11, 0xffff);

        if (ndf.Save(fileName, metaFileName))
            std::cout << "Saved to " << fileName << " and " << metaFileName << '\n';
        else
            std::cout << "Failed to save data to " << fileName << " and " << metaFileName << '\n';

        if (ndf.Load(fileName, metaFileName))
            std::cout << "Loaded from " << fileName << " and " << metaFileName << '\n';
        else
            std::cout << "Failed to load data from " << fileName << " and " << metaFileName << '\n';

        ndf.Dump();
        std::cout << ndf[0] << '\n';
        std::cout << ndf[1] << '\n';
        std::cout << ndf[10] << '\n';
        std::cout << ndf[11] << '\n';
    }

    return 0;
}
