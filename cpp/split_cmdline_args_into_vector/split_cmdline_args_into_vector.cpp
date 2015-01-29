// 2015-01-28T12:00+08:00

#include <string>
#include <vector>

#include "../common.h"
#include "../split_args.h"

int main()
{
    std::string cmdline_string;
    std::vector<std::string> vargs;

    while (std::getline(std::cin, cmdline_string)) {
#if 0
        SplitArgs(cmdline_string, vargs);
#else
        SplitArgsEx(cmdline_string, vargs);
#endif

        //std::cout << vargs << std::endl;
        Println(vargs);
    }

    return 0;
}
