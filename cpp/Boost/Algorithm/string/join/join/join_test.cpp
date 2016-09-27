// 2016-09-27T14:56+08:00
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm_ext.hpp>

#include "../../../../../common.h"


int main()
{
    std::vector<std::string> stringVector { "Hello", "world!" };
    std::cout << boost::join(stringVector, ", ") << std::endl;

    int arr[] { 0, 1, 2, 3, 4 };
    int arr2[]{ 5, 6, 7, 8, 9 };

    std::vector<int> vals;
    boost::push_back(vals, arr);
    boost::push_back(vals, arr2);

    std::cout << boost::join(
        vals
        | boost::adaptors::transformed(boost::math::pow<2, int>)
        | boost::adaptors::filtered([](int val) { return val % 2 == 0; })
        | boost::adaptors::transformed(boost::lexical_cast<std::string, int>),
        ", ") << std::endl;

    PAUSE();
    return 0;
}

// References:
// https://www.zhihu.com/question/36642771