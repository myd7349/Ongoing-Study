#include "pch.h"
#include "PEModule.h"


int main()
{
    examples::dllexport::basicExport::PEModule lib(_T("HelloCSharp.dll"));

    // In the manner of Conari syntax: https://github.com/3F/Conari
    auto result = lib.call<int, int>("Add", 1, 2);
    std::cout << "1 + 2 == " << result << std::endl;
    std::cin.get();

    return 0;
}


// References:
// https://github.com/3F/DllExport/wiki/Quick-start
// https://github.com/3F/Examples/tree/master/DllExport/BasicExport
// [Conari vs .NET DllExport; Unmanaged C++ and C# [ Part-1 ]](https://www.youtube.com/watch?v=9Hyg3_WE9Ks)
