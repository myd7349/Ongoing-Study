// 2015-10-19T14:16+08:00
#include <iostream>
#include <string>
#include <vector>

#define HAS_BOOST (0)

#if HAS_BOOST
# include <boost/algorithm/string.hpp>
#endif

#include "../../../../common.h"
#include "../../../../join.hpp"
#include "../../../../split.hpp"


#define PRINT_(fun, s, delimiter, keepEmptyParts) \
    do { \
        std::cout << #fun << "(\"" << s << "\", \"" << delimiter << "\", " << keepEmptyParts << "): "; \
        Println(fun<string_list>(s, delimiter, keepEmptyParts)); \
    } while (0)

#define PRINT(s, delimiter, keepEmptyParts) \
    PRINT_(split, s, delimiter, keepEmptyParts); \
    PRINT_(split_by_tokens, s, delimiter, keepEmptyParts);


int main()
{
    typedef std::vector<std::string> string_list;

    std::string str = "GOROOT=D:\\go;GOPATH=D:\\study\\go;OS=Windows_NT";

    string_list tokens;

#if HAS_BOOST
    boost::split(tokens, str, boost::is_any_of("=;"));
#else
    tokens = split_by_tokens<string_list>(str, "=;");
#endif

    Println(tokens);
    std::cout << join(tokens.cbegin(), tokens.cend(), '\n') << std::endl;

    PRINT("abc", "", true);
    PRINT("", "", true);
    PRINT("", "abc", true);
    PRINT("a,b,,c,", ",", true);


    // TODO:
    // Use RegEx as a splitter.

    return 0;
}

// References:
// http://www.zhihu.com/question/36642771
