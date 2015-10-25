// 2015-10-25T13:37+08:00
#include <cstddef>
#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>
#include <boost/utility/string_ref.hpp>

#include "../../../../common.h"

// Algorithms, Fourth Edition, P204
// > String values and substrings. A String of length N typically uses 40 bytes
//   (for the String object) plus 24 + 2N bytes(for the array that contains the
//   characters) for a total of 64 + 2N bytes.But it is typical in string processing 
//   to work with substrings, and Java's representation is meant to allow us to do
//   so without having to make copies of the string's characters. When you use the 
//   substring() method, you create a new String object(40 bytes) but reuse the same
//   value[] array, so a substring of an existing string takes just 40 bytes.The 
//   character array containing the original string is aliased in the object for
//   the substring; the offset and length fields identify the substring.In other words,
//   a substring takes constant extra memory and forming a substring takes constant time,
//   even when the lengths of the string and the substring are huge.A naive representation
//   that requires copying characters to make substrings would take linear time and space.
//   The ability to create a substring using space (and time) independent of its length is
//   the key to efficiency in many basic string - processing algorithms.

void pass_a_str_copy(const std::string &str_copy, std::size_t &pos)
{
    pos = str_copy.find_last_of("dog");
}

void pass_a_str_view(const boost::string_ref &str_view, std::size_t &pos)
{
    pos = str_view.find_last_of("dog");
}

int main()
{
    const char *str = "The quick brown fox jumps over the lazy dog.";
    const int COUNT = 100000;
    std::size_t pos;

    // 
    {
        boost::timer::auto_cpu_timer timer;
        for (int i = 0; i < COUNT; ++i)
            pass_a_str_copy(str, pos);
    }
    std::cout << pos << std::endl;

    //
    {
        boost::timer::auto_cpu_timer timer;
        for (int i = 0; i < COUNT; ++i)
            pass_a_str_view(str, pos);
    }
    std::cout << pos << std::endl;

    PAUSE();
    return 0;
}

// References:
// Ongoing-Study/cpp/Boost/Algorithm/string/split
// http://www.zhihu.com/question/36642771
// [muduo::StringPiece](http://www.zhihu.com/question/34499426)
// 