// 2017-07-27T16:30+08:00
#include <cstdio>
#include <iostream>
#include <string>

#include "Abs.hpp"


template <typename T>
T AbsNotSoCool(T x)
{
    if (x <= T())
        return -x;
    else
        return x;
}


int main()
{
    std::cout << std::to_string(AbsNotSoCool(0.0)) << std::endl;

    char buffer[100];
    std::sprintf(buffer, "%.2f", AbsNotSoCool(0.0));
    std::cout << buffer << std::endl;

    std::cout << std::to_string(Abs(0.0)) << std::endl;

    return 0;
}

// Output:
/*
-0.000000
-0.00
0.000000
*/

/*
 So:

double ReturnNonPositiveValue()
{
	...
}

double nonPositiveValue = ReturnNonPositiveValue();

// Not Cool!
double nonNegativeValue = -nonPositiveValue;
std::to_string(nonNegativeValue); // we may got -0.000000 here.

// Cool!
double nonNegativeValue = Abs(nonPositiveValue);
std::to_string(nonNegativeValue);
*/
