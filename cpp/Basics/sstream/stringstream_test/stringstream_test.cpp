#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>


template <typename T>
bool convert(const std::string &s, T &value)
{
    std::stringstream ss;
    ss << s;
    ss >> value;
    if (!ss)
        value = T();
    return ss;
}


int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 2)
    {
        std::stringstream ss;
        ss << argv[0] << " " << "placeholder" << " " << (argc == 1 ? "42" : argv[1]) << std::ends;

        if (std::system(ss.str().c_str()) != 0)
            return EXIT_FAILURE;
    }
    else
    {
        std::string s = argv[2];
        double answer;

        if (convert(s, answer))
            std::cout << "The answer is: " << answer << std::endl;
        else
            std::cout << "You must be John Snow cause you know nothing about The Universe!" << std::endl;
    }

    return EXIT_SUCCESS;
}


// References:
// https://www.boost.org/doc/libs/1_65_1/doc/html/interprocess/quick_guide.html
// Multithreading Applications in Win32, Ch13, P283
