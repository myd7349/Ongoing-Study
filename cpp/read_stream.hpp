// 2015-10-19T15:48+08:00
#ifndef READ_STREAM_H_
#define READ_STREAM_H_

#include <algorithm>
#include <iosfwd>
#include <iterator>
#include <string>
#include <vector>

namespace detail {
template <typename CharT>
class Line : public std::basic_string<CharT> {
    friend std::basic_istream<CharT> &operator>>(std::basic_istream<CharT> &is, Line &line) {
        std::getline(is, line);
        if (is)
            line += (CharT)'\n';
        return is;
    }
};
}

// Read in-stream line by line.
template <typename CharT>
std::vector<std::basic_string<CharT>> read_stream(std::basic_istream<CharT> &is)
{
    using LineIter = std::istream_iterator<detail::Line<CharT>>;

    std::vector<std::basic_string<CharT>> lines;
    std::copy(LineIter(is), LineIter(), std::back_inserter(lines));

    return lines;
}


#endif // READ_STREAM_H_

// References:
// [Is there a C++ iterator that can iterate over a file line by line?](http://stackoverflow.com/questions/2291802/is-there-a-c-iterator-that-can-iterate-over-a-file-line-by-line)
// [Reading data from a single column .csv file in C++](https://stackoverflow.com/questions/32635244/reading-data-from-a-single-column-csv-file-in-c)
// [c++ reading csv file](https://stackoverflow.com/questions/19936483/c-reading-csv-file/19936571#19936571)
