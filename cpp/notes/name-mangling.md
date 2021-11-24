[cppmangle](https://github.com/AVGTechnologies/cppmangle)

[Function to mangle/demangle functions](https://stackoverflow.com/questions/4939636/function-to-mangle-demangle-functions)

[MSVC C++ Name Mangling From String On Runtime](https://stackoverflow.com/questions/55159432/msvc-c-name-mangling-from-string-on-runtime)

[Dependencies](https://github.com/lucasg/Dependencies) uses [llvm-demangle](https://github.com/lucasg/Dependencies/tree/master/third_party/llvm-demangle) and [demumble](https://github.com/nico/demumble) to do demangling.

https://github.com/horsicq/XDemangle

[folly/Demangle.h at main · facebook/folly · GitHub](https://github.com/facebook/folly/blob/main/folly/Demangle.h)

[GitHub - nico/demumble: A better c++filt and a better undname.exe, in one binary.](https://github.com/nico/demumble)

[c++filt (GNU Binary Utilities)](https://sourceware.org/binutils/docs/binutils/c_002b_002bfilt.html)

https://stackoverflow.com/questions/4465872/why-does-typeid-name-return-weird-characters-using-gcc-and-how-to-make-it-prin

```cpp
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cxxabi.h>


std::string demangle(const char *mangledName)
{
    assert(mangledName != nullptr);

    int status;
    char *demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);

    if (demangledName != nullptr) {
        std::string realName = demangledName;
        std::free(demangledName);
        return realName;
    } else {
        return mangledName;
    }
}


#define TN(t) (demangle(typeid(t).name()))
#define TEST(t) std::cout << TN(t) << std::endl

int f(int arg0, double arg1, std::string arg2, const char *arg3, int* arg4, std::string& arg5);

int main()
{
    TEST(int);
    TEST(std::basic_string<char>);

    std::cout << typeid(f).name() << std::endl;
    TEST(f);

    return 0;
}

```

[C++ 如何获取函数的原型?](https://www.zhihu.com/question/278587865/answer/401159650)