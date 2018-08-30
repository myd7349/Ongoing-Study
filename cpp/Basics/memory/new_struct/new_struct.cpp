#include <iostream>
#include <memory>


struct Config
{
    Config()
    {
        value = 42;
    }

    int value;
};

int main()
{
    std::unique_ptr<Config> p1(new struct Config);
    std::unique_ptr<Config> p2(new struct Config());
    std::unique_ptr<Config> p3(new Config);
    std::unique_ptr<Config> p4(new Config());

    std::cout << p1->value << std::endl;
    std::cout << p2->value << std::endl;
    std::cout << p3->value << std::endl;
    std::cout << p4->value << std::endl;

    return 0;
}

// VS2017
// 42
// 42
// 42
// 42

