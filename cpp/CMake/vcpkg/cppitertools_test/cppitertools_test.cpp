#include <iostream>

#include <range.hpp>


int main()
{
    for (auto i : iter::range(20, 30, 2))
        std::cout << i << '\n';
}
