// 2015-02-10T10:22+08:00
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <typeinfo>
#include <unordered_set>

#define CONFIG_USING_BOOST (0)
#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

// Q1: Is STL's set an unordered set?
// Answer:
// http://www.cplusplus.com/reference/set/set/
// Sets are containers that store unique elements following a specific order.
//
// Internally, the elements in a set are always sorted following a specific
// strict weak ordering criterion indicated by its internal comparison object
// (of type Compare).
//
// By default, std::set use a std::less object as its comparison object.
void Q1_test()
{
    std::cout << __func__ << ":" << std::endl;
    std::set<std::string> commands {"ls", "rm", "man", "cd", "tee", "ps", "gcc"};
    for (const auto &cmd : commands) {
        std::cout << cmd << " ";
    }
    std::cout << std::endl;
}

// Q2: Can we sort a set by calling std::sort?
// Answer:
// http://stackoverflow.com/questions/13385348/sorting-sets-using-stdsort
void Q2_test()
{
    std::cout << __func__ << ":" << std::endl;
    std::set<int> integer_set {3, 2, 7, 5, 0, 9, 1};

    // For std::set, iterator and const_iterator are the same type.
    assert(typeid(std::set<int>::iterator) == typeid(std::set<int>::const_iterator));
    // std::sort needs random access iterator, but std::set<T>::iterator
    // is a bidirectional access iterator.
    std::cout << TYPE_NAME(std::set<int>::iterator::iterator_category) << std::endl;

    // http://www.cplusplus.com/reference/set/set/
    // The value of the elements in a set cannot be modified once in the container
    // (the elements are always const), but they can be inserted or removed from the
    // container.
#if 0
    std::sort(integer_set.begin(), integer_set.end()); // Oops! We can not and needn't.
#endif

    // If you'd like to change the default comparison object, then:
    std::set<std::string, std::greater<std::string>> commands {"ls", "rm", "man", "cd", "tee", "ps", "gcc"};
    for (const auto &cmd : commands) {
        std::cout << cmd << " ";
    }
    std::cout << std::endl;
}

// Q3: What's the difference between std::set and std::unordered_set(Since C++11)?
// Answer:
// http://stackoverflow.com/questions/16075890/what-is-the-difference-between-set-and-unordered-set-in-c
void Q3_test()
{
    std::cout << __func__ << ":" << std::endl;
}

// Q4: http://www.zhihu.com/question/20654571
// 
void Q4_test()
{
    std::cout << __func__ << ":" << std::endl;

    class Re {
    public:
        int End;
        bool operator<(const Re &parm) const {
            return End < parm.End;
        }
    };

    std::set<Re> myset;
    Re obj;
    myset.insert(obj);
}

int main()
{
    Q1_test();
    Q2_test();
    Q3_test();
    Q4_test();

    PAUSE();
    return 0;
}

