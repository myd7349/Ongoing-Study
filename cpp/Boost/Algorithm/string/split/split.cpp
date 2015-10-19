// 2015-10-19T14:16+08:00
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "../../../../common.h"

int main()
{
    std::string str = "GOROOT=D:\\go;GOPATH=D:\\study\\go;OS=Windows_NT;";

    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of("=;"));

    Println(tokens);

    // TODO:
    // Use RegEx as a splitter.

    return 0;
}

// References:
// [c++的string为什么不提供split函数？](http://www.zhihu.com/question/36642771)
