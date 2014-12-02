// 2014-12-02T16:30+08:00
// In C++, we can use typeid operator to get the RTTI of an expression or a type.
// However, different C++ compilers provide different type names when we wrote:
//     std::cout << typeid(type/expression).name();
// The names returned by g++ is extremely unreadable, so I just STFG and wrote this sample.

#include <initializer_list>
#include <iostream>
#include <typeinfo>

// What predefined macro can I use to detect clang/gcc/msvc?
// http://nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros
// http://stackoverflow.com/questions/2658461/what-predefined-macro-can-i-use-to-detect-clang
#if defined(__clang__)

# define TYPE_NAME(exp) (typeid(exp).name())
# error Not tested yet!

#elif defined(__GNUC__) || defined(__GNUG__)

// The type name we got from g++ is a decorated name, so we need demangle it.
// http://stackoverflow.com/questions/4465872/why-typeid-name-returns-weird-characters-using-gcc
// https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
# include <cassert>
# include <string>
# include <cxxabi.h>

std::string demangle(const char *mangledName)
{
    assert(mangledName != nullptr);

    int status;
    char *demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);

    if (demangledName != nullptr) {
        std::string realName = demangledName;
        delete demangledName;
        return realName;
    } else {
        return mangledName;
    }
}

# define TYPE_NAME(exp) (demangle(typeid(exp).name()))

#elif defined(_MSC_VER)

# define TYPE_NAME(exp) (typeid(exp).name())

#endif

int main()
{
    std::cout << TYPE_NAME(int) << std::endl; // int
    std::cout << TYPE_NAME(1 < 2) << std::endl; // bool

#if defined(_MSC_VER)
	auto lst = new std::initializer_list<int>({1, 2, 3, 4});
#else
	// In VS2013, code below causes an compile-time error.
	auto lst = new auto({1, 2, 3, 4}); // C++11 is needed.
#endif
    std::cout << TYPE_NAME(lst) << std::endl; // std::initializer_list<int>*
    delete lst;

    return 0;
}
