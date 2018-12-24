// 2015-01-22T16:59+08:00

// Some frequently used stuffs.

#ifndef COMMON_H_
#define COMMON_H_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
# define _CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef CONFIG_USING_BOOST
# define CONFIG_USING_BOOST (0)
#endif

// CONCAT
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

// STR
#ifndef STR
#  define STR_IMPL(c) #c
#  define STR(c) STR_IMPL(c)
#endif

// __func__
// http://stackoverflow.com/questions/15126387/func-c11-functions-local-predefined-variable-wont-compile
// http://stackoverflow.com/questions/2281970/cross-platform-defining-define-for-macros-function-and-func
#if defined(_MSC_VER) && !defined(__func__)
#  define __func__ __FUNCTION__
#endif

// PAUSE
#ifdef _MSC_VER
# ifdef NDEBUG
#  define PAUSE() (__noop)
# else
#  define PAUSE() std::system("pause")
# endif
#else
# define PAUSE() ((void)0)
#endif

// RETURN_ON_FAILURE
#define RETURN_ON_FAILURE_MSG(msg) std::cerr << msg << ": " << e.what() << '\n'; PAUSE(); return EXIT_FAILURE
#define RETURN_ON_FAILURE() std::cerr << e.what() << '\n'; PAUSE(); return EXIT_FAILURE
#define RETURN_ON_FAILURE_MSG_NO_PAUSE(msg) std::cerr << msg << ": " << e.what() << '\n'; return EXIT_FAILURE
#define RETURN_ON_FAILURE_NO_PAUSE() std::cerr << e.what() << '\n'; return EXIT_FAILURE

// GetProgName
#if defined(CONFIG_USING_BOOST) && CONFIG_USING_BOOST
# include <boost/filesystem.hpp>
template <typename charT>
inline std::basic_string<charT> GetProgName(const std::basic_string<charT> &argv0)
{
    return boost::filesystem::path(argv0).stem().string<std::basic_string<charT>>();
}
#else
#define _DEFINE_GETPROGNAME(charT, pathsep, dot) \
    inline std::basic_string<charT> GetProgName(const std::basic_string<charT> &argv0) \
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
inline std::basic_string<charT> GetProgName(const charT *argv0)
{
    return GetProgName(std::basic_string<charT>(argv0));
}

// ARRAYSIZE
// %{
// 2015-09-03T12:10+08:00
// Google/benchmark/macros.h:arraysize 
// %}
#ifndef ARRAYSIZE
# ifdef _MSC_VER
#  define ARRAYSIZE _countof
# else
template <typename T, std::size_t N>
char (*_array_size_helper(T (&)[N]))[N];
#  define ARRAYSIZE(array) (sizeof(*_array_size_helper(array)))
# endif
#endif

// ArraySize
template <typename T, std::size_t N>
inline std::size_t ArraySize(T (&)[N])
{
    return N;
}

// Println
template <typename Iter>
inline void Println(Iter begin, Iter end)
{
    using ValueT = typename std::iterator_traits<Iter>::value_type;

    std::cout << "< ";
    std::copy(begin,
              end,
              std::ostream_iterator<ValueT>(std::cout, " "));
    std::cout << ">\n";
}

#if 0
// https://github.com/adob/print-stmt
// http://stackoverflow.com/questions/4850473/pretty-print-c-stl-containers
template <typename Container, typename CharT>
inline std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> &os, const Container &c)
{
    for (const auto &elem : c) {
        os << '<' << elem << '>';
    }

    return os;
}
#endif

template <typename Container>
inline void Println(const Container &c)
{
    for (const auto &elem : c) {
        std::cout << '<' << elem << '>';
    }

    std::cout << std::endl;
}

// lichray's idea:
// https://github.com/lichray/xrangexx/blob/master/xrange.h
// assert(0 <= b && "invalid range");
// https://github.com/lhmouse/asteria/blob/master/asteria/src/rocket/assert.hpp
#define Assert(expr, msg) assert(((void)msg, expr))

#ifdef NDEBUG
# define Verify(exp) (exp)
#else
# define Verify(exp) assert(exp)
#endif

#ifdef _MSC_VER
# define NOVTABLE __declspec(novtable)
#else
# define NOVTABLE
#endif

// To be continued...

#endif // COMMON_H_
// -- The End --

// References:
// https://stackoverflow.com/questions/1787752/is-there-a-g-equivalent-to-visual-studios-declspecnovtable
