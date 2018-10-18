#include <cassert>
#include <iostream>
#include <list>
#include <iterator>

#include "../../common.h"
#include "../../dividing_lines.h"


std::ostream &operator<<(std::ostream &os, const std::list<int> &list)
{
    bool first = true;

    os << '(';

    for (auto &i : list)
    {
        if (first)
        {
            first = false;
            os << i;
        }
        else
        {
            os << ", " << i;
        }
    }

    return os << ")\n";
}


// 1. void splice( const_iterator pos, list& other );
// Transfers all elements from other.
void test0()
{
    std::list<int> list1{ 1, 2, 3, 4, 5 };
    std::list<int> list2{ 10, 20, 30, 40, 50 };

    auto list1_begin = list1.cbegin();
    assert(list1_begin == list1.cbegin());

    auto list2_begin = list2.cbegin();

    list2.splice(list2.cbegin(), list1);
    std::cout << list1;
    std::cout << list2;

    assert(list1_begin == list2.cbegin());
    assert(list2.cbegin() != list2_begin);

    std::cout << *list2_begin << std::endl;
}


// void splice( const_iterator pos, list& other, const_iterator it );
// Transfer the element pointed by it.
void test1()
{
    std::list<int> list1{ 1, 2, 3, 4, 5 };
    std::list<int> list2{ 10, 20, 30, 40, 50 };

    auto list1_begin = list1.cbegin();
    assert(list1_begin == list1.cbegin());

    list2.splice(list2.cbegin(), list1, list1_begin);
    std::cout << list1;
    std::cout << list2;

    assert(list1_begin == list2.cbegin());
}


// void splice( const_iterator pos, list& other, const_iterator first, const_iterator last);
// Transfers the elements in the range [first, last) from other into *this.
void test2()
{
    std::list<int> list1{ 1, 2, 3, 4, 5 };
    std::list<int> list2{ 10, 20, 30, 40, 50 };

    auto first = list1.cbegin();
    std::advance(first, 1);

    auto last = first;
    std::advance(last, 3);

    auto pos = list2.cbegin();
    std::advance(pos, 1);

    list2.splice(pos, list1, first, last);
    std::cout << list1;
    std::cout << list2;

    std::cout << *pos << std::endl;
    std::cout << *first << std::endl;
    std::cout << *last << std::endl;
}


int main()
{
    DIVIDING_LINE_1('-');
    test0();

    DIVIDING_LINE_1('-');
    test1();

    DIVIDING_LINE_1('-');
    test2();

    PAUSE();

    return 0;
}


// References:
// cppreference:splice
// C++ Concurrency in Action, Ch4.4.1
