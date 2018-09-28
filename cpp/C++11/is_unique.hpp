#pragma once

#include <algorithm>
#include <iterator>
#include <set>


template <typename InputIt>
bool is_unique_impl_old_school(InputIt first, InputIt last)
{
    InputIt next = first;
    std::advance(next, 1);

    for (; next != last;)
    {
        auto it = std::find(next, last, *first);
        if (it != last)
            return false;

        first = next;
        std::advance(next, 1);
    }

    return true;
}


// Warning: This implementation will change the original container.
template <typename RandomIt>
bool is_unique_impl_using_sort(RandomIt first, RandomIt last)
{
    std::sort(first, last);

    RandomIt next = first;
    std::advance(next, 1);

    for (; next != last;)
    {
        if (*next == *first)
            return false;

        first = next;
        std::advance(next, 1);
    }

    return true;
}


template <typename InputIt>
bool is_unique_impl_with_set(InputIt first, InputIt last)
{
    std::set<decltype(*first)> set(first, last);
    return std::distance(first, last) == set.size();
}
