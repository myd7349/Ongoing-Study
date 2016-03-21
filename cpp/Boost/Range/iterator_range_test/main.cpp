// 2016-03-21T14:11+08:00
#include <cstring>
#include <iostream>
#include <iterator>

#include <boost/range/istream_range.hpp>


int main()
{
    const char *what = "Hello, world!";
    boost::iterator_range<const char *> range(what, what + std::strlen(what));

    for (auto ch : range)
        std::cout << ch;

    std::cout << std::endl;

    char hello[] = "Hello, world!";
    for (auto it = std::begin(hello); it != std::end(hello); ++it)
        std::cout << *it;

    return 0;
}

// References:
// [RAW pointer container wrapper](http://stackoverflow.com/questions/4291583/raw-pointer-container-wrapper)
