#include <ctime>
#include <iomanip>
#include <iostream>


int main()
{
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);
    std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S%n");

    char buffer[128] {};
    if (std::strftime(buffer, sizeof(buffer) / sizeof(buffer[0]), "%Y-%m-%d %H:%M:%S%n", tm) > 0)
        std::cout << buffer;

    std::cin.get();

    return 0;
}
