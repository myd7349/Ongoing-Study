#include <iostream>

#include <opencc/opencc.h>
#include <opencc/SimpleConverter.hpp>

#ifdef _WIN32
# include "../../../../c/Win32/wconv.h"
#else
# define Utf8ToAnsi(x) (x)
#endif


int main()
{
    opencc::SimpleConverter converter(OPENCC_DATA_PATH OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD);
    std::cout << Utf8ToAnsi(converter.Convert("计算机程序设计的艺术")) << std::endl;
    std::cout << Utf8ToAnsi(converter.Convert("单例模式")) << std::endl;
    return 0;
}
