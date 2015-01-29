// 2015-01-29T09:42+08:00

#ifndef SPLIT_ARGS_H_
#define SPLIT_ARGS_H_

#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>
#include <string>

#if defined(__GNUC__)
// <regex> is implemented and released in GCC 4.9.0.
# if __GNUC__ > 4 || \
    (__GNUC__ == 4 && (__GNUC_MINOR__ > 9 || \
                      (__GNUC_MINOR__ == 9 && \
                       __GNUC_PATCHLEVEL__ > 0)))
#  include <regex>
#  define RE std
# else
#  define USING_BOOST_REGEX_INSTEAD
# endif
#elif defined(_MSC_VER)
# if _MSC_VER >= 1600
#  include <regex>
# else
#  define USING_BOOST_REGEX_INSTEAD
# endif
#else
# error Not tested yet!
# define USING_BOOST_REGEX_INSTEAD
#endif

#ifdef USING_BOOST_REGEX_INSTEAD
# include <boost/regex.hpp>
# define RE boost
#endif

// Split command line string into a vector.
// (Use space as the argument delimiter.)
template <typename CharT>
typename std::vector<std::basic_string<CharT>>::size_type
SplitArgs(const std::basic_string<CharT> &cmdline_str,
          std::vector<std::basic_string<CharT>> &xargs)
{
    xargs.clear();

    std::basic_istringstream<CharT> iss(cmdline_str);

    std::istream_iterator<std::basic_string<CharT>> it(iss), eos;
    std::copy(it, eos, std::back_inserter(xargs));

    return xargs.size();
}

template <typename CharT>
typename std::vector<std::basic_string<CharT>>::size_type
SplitArgs(const CharT *cmdline_str,
          std::vector<std::basic_string<CharT>> &xargs)
{
    assert(cmdline_str != nullptr);
    return SplitArgs(std::basic_string<CharT>(cmdline_str), xargs);
}

// Split command line string into a vector.
// This version is able to handle arguments that contain space characters.
template <typename CharT>
typename std::vector<std::basic_string<CharT>>::size_type
SplitArgsEx(const std::basic_string<CharT> &cmdline_str,
          std::vector<std::basic_string<CharT>> &xargs)
{
    xargs.clear();

    // \s*([^\s"]+|"[^"]*")
    //const char *re = R"(\s*([^\s"]+|"[^"]*"))";
#ifndef USING_BOOST_REGEX_INSTEAD
    RE::basic_regex<CharT> arg_re {
        ' ', '*',                              // Zero or more space characters
        '(',                                   // Group begin
            '[', '^', ' ', '"', ']', '+',          // one or more characters that are neither space nor double-quote
            '|',                                   // or
            '"', '[', '^', '"', ']', '*', '"',     // something quoted by two double quotation marks
                                                   // (A file path name that contains space character, for instance)
        ')',                                   // Group end
    };
#else
    std::string re(R"(\s*([^\s"]+|"[^"]*"))");
    RE::basic_regex<CharT> arg_re(re.begin(), re.end());
#endif

    using StringIterator = typename std::basic_string<CharT>::const_iterator;

    RE::regex_iterator<StringIterator> rit(cmdline_str.begin(), cmdline_str.end(), arg_re);
    RE::regex_iterator<StringIterator> rend;

    std::basic_string<CharT> arg;

    while (rit != rend) {
        const auto &match_res = *rit;
        arg = match_res[1].str();
        if (!arg.empty()) {
            if ((CharT)'"' == arg[0]) {
                assert(arg.size() >= 2);
                arg = arg.substr(1, arg.size() - 2);
            }

            if (!arg.empty()) {
                xargs.push_back(arg);
            }
        }

        ++rit;
    }

    return xargs.size();
}

template <typename CharT>
typename std::vector<std::basic_string<CharT>>::size_type
SplitArgsEx(const CharT *cmdline_str,
          std::vector<std::basic_string<CharT>> &xargs)
{
    assert(cmdline_str != nullptr);
    return SplitArgsEx(std::basic_string<CharT>(cmdline_str), xargs);
}

#endif // SPLIT_ARGS_H_

// References:
// [3.7.2 Common Predefined Macros](http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html)
// [C/C++ tip: How to detect the compiler name and version using compiler predefined macros](http://nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros)
// [Is gcc4.7 buggy about regular expressions?](http://stackoverflow.com/questions/12530406/is-gcc4-7-buggy-about-regular-expressions)
// [Virtual Studio C++ Version Macro - _MSC_VER](http://blog.csdn.net/nightelve/article/details/16842505)
