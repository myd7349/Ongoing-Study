// 2014-12-08T10:56+08:00
// 2018-04-21T20:57+08:00 https://github.com/facebook/folly/blob/master/folly/Demangle.h
#ifndef UNIFORM_TYPENAME_H_INCLUDED
#define UNIFORM_TYPENAME_H_INCLUDED

// 2015-08-26T22:22+08:00 TODO: Boost.Predef
// What predefined macro can I use to detect clang/gcc/msvc?
// http://nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros
// http://stackoverflow.com/questions/2658461/what-predefined-macro-can-i-use-to-detect-clang
#if defined(__clang__)
//# define TYPE_NAME(exp) (typeid(exp).name())
# error Not tested yet!
#elif defined(__GNUC__) || defined(__GNUG__)
// The type name we got from g++ is a decorated name, so we need demangle it.
// http://stackoverflow.com/questions/4465872/why-typeid-name-returns-weird-characters-using-gcc
// https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
# include <cassert>
# include <cstdlib>
# include <string>
# include <cxxabi.h>

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

# define TYPE_NAME(exp) (demangle(typeid(exp).name()))
#elif defined(_MSC_VER)
# define TYPE_NAME(exp) (typeid(exp).name())
#endif

#endif // UNIFORM_TYPENAME_H_INCLUDED


// References:
// https://www.zhihu.com/question/278587865
