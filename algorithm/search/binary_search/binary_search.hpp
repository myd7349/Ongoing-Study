#ifndef BINARY_SEARCH_HPP_
#define BINARY_SEARCH_HPP_

#include <functional>
#include <iterator>


// std::binary_search returns bool.
template <typename ForwardIt, typename T, typename CompareT>
inline bool binary_search(ForwardIt first, ForwardIt last, const T &value, CompareT comp)
{
    while (first != last)
    {
        auto middle = first;
        std::advance(middle, std::distance(first, last) / 2);

        if (comp(*middle, value)) // *middle < value
        {
            std::advance(middle, 1);
            first = middle;
        }
        else if (comp(value, *middle)) // value < *middle
        {
            last = middle;
        }
        else
        {
            return true;
        }
    }

    return false;
}


template <typename ForwardIt, typename T>
inline bool binary_search(ForwardIt first, ForwardIt last, const T &value)
{
    return ::binary_search(first, last, value, std::less<T>()); // The :: operator here is necessary.
}


#endif // BINARY_SEARCH_HPP_


// References:
// C++ Primer, 5th Edition, Ch3
