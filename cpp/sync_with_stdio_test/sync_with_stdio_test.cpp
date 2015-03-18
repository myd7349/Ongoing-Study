// 2014-08-29T14:25+08:00
#include <cstdio>
#include <iostream>

int main()
{
    // ISO C++11 27.5.3.4
    // bool sync_with_stdio(bool sync = true);
    // Returns: true if the previous state of the standard iostream
    // objects (27.4) was synchronized and otherwise returns false.
    // The first time it is called, the function returns true.
    //
    // cplusplus:
    // std::ios_base::sync_with_stdio
    // By default, iostream objects and cstdio streams are synchronized
    // (as if this function was called with true as argument).
    bool res = std::ios::sync_with_stdio();
    std::cout << std::boolalpha << res << std::endl;

    std::cout << "Hello, ";
    std::printf("world!\n");

    return 0;
}
