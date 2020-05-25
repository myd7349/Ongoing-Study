#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstddef>


template <typename T>
class Array
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;

};

#endif // ARRAY_H_
