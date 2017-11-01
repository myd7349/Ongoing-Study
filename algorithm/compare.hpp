// 2017-11-01T09:07+08:00
#ifndef COMPARE_HPP_
#define COMPARE_HPP_

template <typename T>
inline int Compare(T lhs, T rhs)
{
    return (lhs > rhs) - (lhs < rhs);
}

#endif // COMPARE_HPP_

// References:
// http://en.cppreference.com/w/c/algorithm/qsort
