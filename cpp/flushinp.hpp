#pragma once

#include <limits>
#include <istream>


template <typename CharT>
void flushinp(std::basic_istream<typename CharT> &is, CharT delim)
{
    is.ignore(std::numeric_limits<std::streamsize>::max(), delim);
}


// References:
// [How do I flush the cin buffer?](https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer)
