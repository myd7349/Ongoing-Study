// 2014-07-28T09:33+08:00
#include <array>
#include <iostream>
#include <iterator>

int main()
{
    std::array<int, 6> iarr = {42, 1, 2, 3, 4, 5};

    typedef std::array<int, 6>::iterator iter_t;
    typedef std::reverse_iterator<iter_t> rev_iter_t;

    for (iter_t i = iarr.begin(); i != iarr.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    rev_iter_t end(iarr.begin());
    // error:
    // for (rev_iter_t i = iarr.end(); i != iarr.begin(); ++i)
    for (rev_iter_t i(iarr.end()); i != end; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    return 0;
}
