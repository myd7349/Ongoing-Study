// 2017-07-27T16:41+08:00
#ifndef ABS_HPP_
#define ABS_HPP_

template <typename T>
T Abs(T x)
{
    if (x < T())
        return -x;
    else
        return x;
}

#endif
