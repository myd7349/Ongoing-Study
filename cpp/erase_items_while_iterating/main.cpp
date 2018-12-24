// 2016-08-05T21:50+08:00
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "../common.h"

int main()
{
    std::list<int> lst { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Erase even numbers in this list while iterating through it.
#if 0
    for (auto it = lst.begin(); it != lst.end(); )
    {
        if (*it % 2 == 0)
            lst.erase(it++);
        else
            ++it;
    }
#else
    for (auto it = lst.begin(); it != lst.end();)
    {
        if (*it % 2 == 0)
            it = lst.erase(it);
        else
            ++it;
    }
#endif

    Println(lst);

    lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // An example from C++ Primer
    // Remove even-valued elements and insert a duplicate of odd-valued elements
    auto it = lst.begin();
    while (it != lst.end())
    {
        if (*it % 2 != 0)
        {
            // >insert inserts before the position it is given and returns
            // an iterator to the inserted element.
            it = lst.insert(it, *it);
            std::advance(it, 2);
        }
        else
        {
            // >the iterator returned from erase denotes the
            // next element in the sequence.
            it = lst.erase(it);
        }
    }

    Println(lst);

    // remove_if test
    lst.remove_if([](int x) { return x > 5; });
    Println(lst);

    // Copy the remaining items into a vector
    std::vector<int> vec;
    vec.reserve(lst.size());
    for (auto item : lst)
        vec.push_back(item);

    Println(vec);

    return 0;
}

// References:
// [Can I remove elements from std::list, when I'm iterating on it?](http://www.stackoverflow.com/questions/4260891/can-i-remove-elements-from-stdlist-when-im-iterating-on-it)
// [Can you remove elements from a std::list while iterating through it?](http://www.stackoverflow.com/questions/596162/can-you-remove-elements-from-a-stdlist-while-iterating-through-it)
// [Deleting elements from STL set while iterating](http://www.stackoverflow.com/questions/2874441/deleting-elements-from-stl-set-while-iterating)
// [Erasing while iterating an std::list](http://www.stackoverflow.com/questions/16269696/erasing-while-iterating-an-stdlist)
// C++ Primer, 5th Edition, Writing Loops That Change a Container
