// 2016-08-10T09:13+08:00
#include <iostream>
#include <vector>

#include "../common.h"

// Q:
// std::vector<int> iv(10);
// iv.reserve(5);
// Then: iv.size() ?

int main()
{
    std::vector<int> iv { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Println(iv);

    iv.reserve(5);
    std::cout << iv.capacity() << " " << iv.size() << std::endl;
    Println(iv);

    iv.reserve(15);
    std::cout << iv.capacity() << " " << iv.size() << std::endl;
    Println(iv);

    return 0;
}

// cplusplus.com:
// void reserve (size_type n);
//
// Request a change in capacity
// Requests that the vector capacity be at least enough to contain n elements.
//
// If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
//
//In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
//
// This function has no effect on the vector size and cannot alter its elements.
