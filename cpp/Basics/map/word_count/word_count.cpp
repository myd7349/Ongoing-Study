#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>


namespace std
{
    inline std::ostream &operator<<(std::ostream &os, const std::pair<std::string, std::size_t> &kv)
    {
        return os << kv.first << ": " << kv.second;
    }
}


std::map<std::string, std::size_t> word_count(std::istream &is)
{
    std::map<std::string, std::size_t> result;

    std::istream_iterator<std::string> isit(is), iseof;

    while (isit != iseof)
        ++result[*isit++];

    return result;
}


void print_result(const std::map<std::string, std::size_t> &result)
{
    std::ostream_iterator<std::pair<std::string, std::size_t>> os(std::cout, "\n");

    for (const auto &kv : result)
#if 1
        os = kv;
#else
        *os++ = kv;
#endif
}


int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            std::ifstream file(argv[i]);
            if (!file)
                std::cerr << "Failed to open \"" << argv[i] << "\"\n";

            auto result = word_count(file);

            file.close();
            
            std::cout << argv[i] << ": --------------------\n";
            print_result(result);
        }
    }
    else
    {
        auto result = word_count(std::cin);
        print_result(result);
    }

    return 0;
}

// References:
// C++ Primer, 5th Edition, 11.1. Using an Associative Container
