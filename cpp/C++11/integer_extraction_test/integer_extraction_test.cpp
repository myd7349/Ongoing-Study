// 2014-08-29T15:00+08:00
#include <iostream>
#include <limits>

int main()
{
    int i;
    std::cout << i << std::endl;

    // cplusplus: cin.fail() is the synonym of cin.operator!()
    //
    // http://www.zhihu.com/question/24317543
    //
    // ISO C++11 27.7.2.2.2 Arithmetic extractors
    // As in the case of the inserters, these extractors
    // depend on the locale's num_get<> (22.4.2.1) object
    // to perform parsing the input stream data.
    // ISO C++11 22.4.2.1.2
    // Stage 3: The sequence of chars accumulated in
    // stage 2 (the field) is converted to a numeric
    // value by the rules of one of the functions
    // declared in the header <cstdlib>:
    // -- For a signed integer value, the function strtoll.
    // -- For an unsigned integer value, the function strtoull.
    // -- For a floating-point value, the function strtold.
    // The numeric value to be stored can be one of:
    // -- zero, if the conversion function fails to convert the
    //   entire field. ios_base::failbit is assigned to err.
    //   (In ISO C++98, there is no this sentence.)
    // -- the most positive representable value, if the field
    //   represents a value too large positive to be represented
    //   in val. ios_base::failbit is assigned to err.
    // -- the most negative representable value or zero for
    //   an unsigned integer type, if the field represents a value
    //   too large negative to be represented in val. ios_base::failbit
    //   is assigned to err.
    // -- the converted value, otherwise.
    while (!(std::cin >> i)) {
        std::cout << i << std::endl;
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}

/*
If "std::cin >> i" is failed:
1. In VS2013, i stays unchanged in debug mode and i is set to 0 in release mode.
2. In GCC 4.8.1, i is set as 0 with: -std=c++98, -std=c++0x, -std=c++11.
3. In VS2010, i stays unchanged.
*/
