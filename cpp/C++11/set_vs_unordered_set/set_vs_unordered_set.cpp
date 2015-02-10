// 2015-02-10T10:22+08:00
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <string>

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
    std::set<std::string> commands {"ls", "rm", "help", "cd", "tee", "ps", "gcc"};
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
}

// Q3: What's the difference between std::set and std::unordered_set(Since C++11)?
// Answer:
// http://stackoverflow.com/questions/16075890/what-is-the-difference-between-set-and-unordered-set-in-c
void Q3_test()
{
}

int main()
{
    Q1_test();
    Q2_test();
    Q3_test();

    return 0;
}

