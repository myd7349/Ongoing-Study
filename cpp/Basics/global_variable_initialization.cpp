#include <iostream>

class MyClass
{
    static const int SIZE = 10;

public:
    void Dump()
    {
        for (int i = 0; i < SIZE; ++i)
            std::cout << array_[i] << " ";

        std::cout << std::endl;
    }

private:
    int array_[SIZE];
};


class MyClassV2
{
    static const int SIZE = 10;

public:
    MyClassV2(int value)
        : value_(value)
    {
    }

    void Dump()
    {
        for (int i = 0; i < SIZE; ++i)
            std::cout << array_[i] << " ";

        std::cout << std::endl;
    }

private:
    int value_;
    int array_[SIZE];
};


MyClass global;
MyClassV2 global2(-1);


int main()
{
    MyClass local;
    MyClassV2 local2(-1);

    global.Dump();
    local.Dump();

    global2.Dump();
    local2.Dump();

    return 0;
}


// References:
// https://stackoverflow.com/questions/2091499/why-are-global-and-static-variables-initialized-to-their-default-values
// https://stackoverflow.com/questions/6032638/default-variable-value
// https://stackoverflow.com/questions/22117310/c-global-variable-initialization-order
