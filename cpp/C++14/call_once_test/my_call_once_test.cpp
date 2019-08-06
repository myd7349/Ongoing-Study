#include <iostream>
#include <mutex>
#include <thread>

#include "../call_once.hpp"


once_flag flag1;


void simple_do_once()
{
    call_once(flag1, []() { std::cout << __FUNCTION__ << std::endl; });
}


once_flag flag2;


void may_throw_function(bool do_throw)
{
    if (do_throw)
    {
        std::cout << __FUNCTION__ << " throws an exception, call_once will retry.\n";
        throw std::exception();
    }

    std::cout << __FUNCTION__ << ": Take it easy! I won't repeat it anymore.\n";
}


void do_once(bool do_throw)
{
    try
    {
        call_once(flag2, may_throw_function, do_throw);
    }
    catch (...)
    {
        std::cout << "Caught an exception!\n";
    }
}


int main()
{
    std::thread st1(simple_do_once);
    std::thread st2(simple_do_once);
    std::thread st3(simple_do_once);
    st1.join();
    st2.join();
    st3.join();

    std::thread t1(do_once, true);
    std::thread t2(do_once, false);
    std::thread t3(do_once, false);
    std::thread t4(do_once, true);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cin.get();

    return 0;
}


// References:
// cppreference
