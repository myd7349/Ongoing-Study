// 2015-01-22T16:59+08:00

// Some frequently used stuffs.

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define CONFIG_USING_BOOST (1)

// PAUSE
#ifdef _MSC_VER
# ifdef NDEBUG
#  define PAUSE() (__noop)
# else
#  include <cstdlib>
#  define PAUSE() std::system("pause")
# endif
#else
# define PAUSE() ((void)0)
#endif

// RETURN_ON_FAILURE
#include <iostream>
#define RETURN_ON_FAILURE_MSG(msg) std::cerr << msg << ": " << e.what() << '\n'; PAUSE(); return EXIT_FAILURE
#define RETURN_ON_FAILURE() std::cerr << e.what() << '\n'; PAUSE(); return EXIT_FAILURE

// getProgName
#include <string>
#if defined(CONFIG_USING_BOOST) && CONFIG_USING_BOOST
# include <boost/filesystem.hpp>
template <typename charT>
std::basic_string<charT> getProgName(const std::basic_string<charT> &argv0) 
{
    return boost::filesystem::path(argv0).stem().string<std::basic_string<charT>>();
}
#else
#define _DEFINE_GETPROGNAME(charT, pathsep, dot) \
    std::basic_string<charT> getProgName(const std::basic_string<charT> &argv0) \
    { \
        auto fileTitle = argv0; \
        auto lastSepPos = argv0.find_last_of(pathsep); \
        if (lastSepPos != std::basic_string<charT>::npos) { \
            fileTitle = argv0.substr(lastSepPos + 1); \
        } \
        auto dotPos = fileTitle.rfind(dot); \
        if (dotPos != std::basic_string<charT>::npos) { \
            fileTitle.erase(dotPos); \
        } \
        return fileTitle; \
    }
// Since we haven't define a portable _T/_TEXT/TEXT/U macro yet, so we are not
// able to wrap those string/character literals with such a macro. That is why
// _DEFINE_GETPROGNAME exists: we can use it to define two overloaded "getProg"s,
// one for char, and the other for wchar_t.
_DEFINE_GETPROGNAME(char, "\\/", '.')
_DEFINE_GETPROGNAME(wchar_t, L"\\/", L'.')
#endif
template <typename charT>
std::basic_string<charT> getProgName(const charT *argv0)
{
    //return getProgName(std::basic_string(argv0)); // ???
    return getProgName(std::basic_string<charT>(argv0));
}

// To be continued...

#endif // -- The End --