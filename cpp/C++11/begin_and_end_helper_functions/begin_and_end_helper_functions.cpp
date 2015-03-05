// 2014-08-20T16:48+08:00
// Function template `std::begin` and `std::end` is added into C++11.
// In some situation, these functions are really useful and convenient.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <valarray>

int main()
{
    std::valarray<int> arr;
    // We can not use std::back_inserter with a C-style array.
    // And since std::valarray doesn't have a `push_back`
    // member function, we can not use std::back_inserter
    // with a std::valarray either. So we `resize` the `arr` and
    // then populate it by calling `std::iota`.
    arr.resize(10);

    // std::valarray doesn't define a sub-type `std::valarray::iterator`,
    // so we use std::begin and std::end here. Otherwise, there is no
    // way to populate this array by calling std::iota.
    std::iota(std::begin(arr), std::end(arr), 0);

    typedef std::valarray<int>::value_type ValueType;

    std::copy(std::begin(arr), std::end(arr),
              std::ostream_iterator<ValueType>(std::cout, " "));
    std::cout << std::endl;

    int raw_arr[5] {1, 2, 3, 4, 5};
    // Old style:
    std::iota(raw_arr,
              raw_arr + sizeof(raw_arr) / sizeof(raw_arr[0]), 0);
    for (auto i : raw_arr) { std::cout << i << ' '; }
    std::cout << std::endl;
    // New style: std::end willpast to end iterator help us calculate the
    // past-the-end iterator of `raw_arr`. It is really a convenient
    // helper function!
    std::iota(std::begin(raw_arr), std::end(raw_arr), 1);
    for (auto i : raw_arr) { std::cout << i << ' '; }
    std::cout << std::endl;

    return 0;
}
