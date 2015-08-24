// 2015-08-24T14:06+08:00
#include <iostream>

#include <boost/predef.h>

int main()
{
#if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0))
    std::cout << "You are using GCC 4.8.0 or newer.\n";
#endif

    // Compiler
    std::cout << "Compiler: ";
#if BOOST_COMP_GNUC
    std::cout << "GCC";
#elif BOOST_COMP_MSVC
    std::cout << "MSVC";
#endif
    std::cout << std::endl;

    // OS
    std::cout << "OS: ";
#if BOOST_OS_WINDOWS
    std::cout << BOOST_OS_WINDOWS_NAME;
#elif BOOST_OS_LINUX
    std::cout << BOOST_OS_LINUX_NAME;
#elif BOOST_OS_MACOS
    std::cout << BOOST_OS_MACOS_NAME;
#endif
    std::cout << std::endl;

    // TODO:
    // WinXP or Win7?
    // C++98/03 or C++11?
    // A readable GCC version number?
    // Get major, minor, patch part from the version number?

    return 0;
}

// Similar Projects:
// [Pre-defined Compiler Macros](http://sourceforge.net/projects/predef/)

// References:
// Ongoing-Study/cpp/split_args.h
// Boost.Predef Documentation
// [Semantic Versioning 2.0.0](http://semver.org/)
// [How to identify platform/compiler from preprocessor macros?](http://stackoverflow.com/questions/4605842/how-to-identify-platform-compiler-from-preprocessor-macros)

