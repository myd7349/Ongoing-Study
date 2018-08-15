#include <iostream>
#include <thread>

#include "../CriticalSection.h"
#include "../SingleLock.h"


int main()
{
    int counter = 0;
    CriticalSection cs;

    auto increment = [&counter, &cs]() {
        for (int i = 0; i < 10000000; ++i)
        {
            SingleLock<CriticalSection> lock(cs);
            counter++;
        }
    };

    auto decrement = [&counter, &cs]() {
        for (int i = 0; i < 10000000; ++i)
        {
            SingleLock<CriticalSection> lock(cs);
            counter--;
        }
    };

    std::thread thread1(increment);
    std::thread thread2(increment);
    std::thread thread3(decrement);
    std::thread thread4(increment);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    std::cout << counter << std::endl;

    return 0;
}
