// 2018-07-05T18:04+08:00
#include <iostream>
#include <memory>


int main()
{
    std::unique_ptr<int> i_ptr(
        new int()
    );
    std::cout << *i_ptr << std::endl;

    const int Length = 10;

    std::unique_ptr<int[]> i_arr(
        new int[Length]()
    );
    for (int i = 0; i < Length; ++i)
        std::cout << i_arr[i] << " ";
    std::cout << std::endl;

    std::shared_ptr<int> i_arr2(
        new int[Length](),
        std::default_delete<int[]>()
    );
    for (int i = 0; i < Length; ++i)
        std::cout << i_arr2.get()[i] << " ";
    std::cout << std::endl;


    return 0;
}


// References:
// https://stackoverflow.com/questions/7546620/operator-new-initializes-memory-to-zero
// cppreference:default_delete
// https://stackoverflow.com/questions/13061979/shared-ptr-to-an-array-should-it-be-used
