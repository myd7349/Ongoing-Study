// 2016-10-21T08:44+08:00
// Tools like `StampVer.exe` accept commandline arguments of format:
// StampVer.exe -k -p"1.2.3.4" -f"1.2.3.4" MyModule.dll
// So give it a try:
// msvc_cmdline_args.exe -p"1.2.3.4" -f"1.2.3.4"
//
#include <iostream>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;

#ifndef NDEBUG
    std::cin.get();
#endif

    return 0;
}

// Reference:
// https://msdn.microsoft.com/en-us/library/17w5ykft.aspx
// Python: subprocess.py/list2cmdline