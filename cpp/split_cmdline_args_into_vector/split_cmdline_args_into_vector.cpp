// 2015-01-28T12:00+08:00

#include <sstream>
#include <string>
#include <vector>

#include "../common.h"

// Split command line string into a vector.
template <typename CharT>
typename std::vector<std::basic_string<CharT>>::size_type
SplitArgs(const std::basic_string<CharT> &cmdline_str,
    std::vector<std::basic_string<CharT>> &xargs)
{
    xargs.clear();

    std::basic_istringstream<CharT> iss(cmdline_str);

    std::istream_iterator<std::basic_string<CharT>> it(iss), eos;
    std::copy(it, eos, std::back_inserter(xargs));

    return xargs.size();
}

int main()
{
    std::string cmdline_string;
    std::vector<std::string> vargs;

    while (std::getline(std::cin, cmdline_string)) {
        SplitArgs(cmdline_string, vargs);
        //std::cout << vargs << std::endl;
        Println(vargs);
    }

    return 0;
}
