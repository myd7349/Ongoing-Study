// 'i' before 'e' except after 'c'
// receipt freind theif receive
#include <fstream>
#include <iostream>
#include <regex>
#include <string>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage:\n  ibeeac [<file>...]\n";
        return 0;
    }

    std::string pattern(
        "[[:alpha:]]*"
        "[^c]ei"
        "[[:alpha:]]*"
    );

    std::regex re(pattern, std::regex::icase);

#if 0
    std::string test_str = " receipt freind theif receive ";
    std::smatch results;
    if (std::regex_search(test_str, results, re))
        std::cout << results.str() << std::endl;
#endif

    std::string line;

    for (int i = 1; i < argc; ++i)
    {
        std::cout << "========== " << argv[i] << " ==========\n";

        std::ifstream file(argv[i]);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file!\n";
            continue;
        }

        while (std::getline(file, line))
        {
            for (std::sregex_iterator it(line.cbegin(), line.cend(), re), end_it;
                it != end_it;
                ++it)
            {
                auto pos = it->prefix().length();
                pos = pos > 40 ? pos - 40 : 0; // we want up to 40 characters
                std::cout
                    << it->prefix().str().substr(pos) // last part of the prefix
                    << "\n\t\t>>> " << it->str() << " <<<\n" // matched word
                    << it->suffix().str().substr(0, 40) // first part of the suffix
                    << std::endl;
            }
        }

        file.close();
    }

    return 0;
}


// References:
// C++ Primer, 5th Edition, 17.3.1 Using the Regular Expression Library
// https://stackoverflow.com/questions/2291802/is-there-a-c-iterator-that-can-iterate-over-a-file-line-by-line
// https://stackoverflow.com/questions/29895519/using-a-regex-iterator-on-an-istream
