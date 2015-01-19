// 2015-01-19T14:10+08:00
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility> // for std::move
#include <vector>

void test_0()
{
    std::vector<int> arr {1, 2, 3, 4};

    std::vector<std::vector<int>> matrix;
    matrix.push_back(std::move(arr));

    // cplusplus says:
    // in the standard library- moving implies that the moved-from object is
    // left in a valid but unspecified state. Which means that, after such an
    // operation, the value of the moved-from object should only be destroyed
    // or assigned a new value; accessing it otherwise yields an unspecified
    // value.
    assert(arr.empty()); // arr MIGHT be empty
}

void test_1()
{
    std::unique_ptr<int> pi(new int(42));
    assert(pi != nullptr && 42 == *pi);

    // transfer ownership
    auto pi2 = std::move(pi);
    assert(nullptr == pi && pi2 != nullptr && 42 == *pi2);
}

// cppreference:
// string move assignment operator is often implemented as swap,
// in this case, the moved-from object is NOT empty
void test_2()
{
    std::string str1 = "Hello";
    std::string str2 = "World";

    str2 = std::move(str1);

    std::cout << str1 << ' ' << str2 << std::endl;
}

int main()
{
    test_0();

    test_1();

    test_2();

    return 0;
}

// References:
// [std::move](http://www.cplusplus.com/reference/utility/move/)
// [std::move](http://en.cppreference.com/w/cpp/utility/move)
// [When should I use std::move in C++11?](http://www.quora.com/When-should-I-use-std-move-in-C++11)
