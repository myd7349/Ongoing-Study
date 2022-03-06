#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <cryptopp/cpu.h>


std::string CpuIdToString(const CryptoPP::word32 (&cpuid)[4])
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    oss << std::setw(8) << cpuid[0]
        << '-'
        << std::setw(8) << cpuid[1]
        << '-'
        << std::setw(8) << cpuid[2]
        << '-'
        << std::setw(8) << cpuid[3];

    return oss.str();
}


int main()
{
    CryptoPP::word32 cpuid[4];
    CryptoPP::CpuId(0, 0, cpuid);
    std::cout << CpuIdToString(cpuid) << std::endl;

    return 0;
}


// References:
// https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-170
// [Getting the machine serial number and CPU ID using C/C++ in Linux](https://stackoverflow.com/questions/6491566/getting-the-machine-serial-number-and-cpu-id-using-c-c-in-linux)
// [CPU ID using C++ - windows](https://stackoverflow.com/questions/21642347/cpu-id-using-c-windows)
// [Get cpuid serial number by C++](https://www.codeproject.com/Questions/1112929/Get-cpuid-serial-number-by-Cplusplus)
// https://en.wikipedia.org/wiki/CPUID
// [What is a good unique PC identifier?](https://stackoverflow.com/questions/3443093/what-is-a-good-unique-pc-identifier)
