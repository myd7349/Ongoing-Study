#include <iostream>
#include <mutex>
#include <thread>

#include "../../common.h"


thread_local int counter = 0;
std::mutex cout_mutex;


void init(int c)
{
    counter = c;
}


void dump()
{
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "#" << std::this_thread::get_id() << ": " << counter << std::endl;
}


void incr(int initial)
{
    init(initial);
    ++counter;
    dump();
}


int main()
{
    counter = 9;

    std::thread t1(incr, 1);
    std::thread t2(incr, 2);
    std::thread t3(incr, 3);

    t1.join();
    t2.join();
    t3.join();

    dump();

    PAUSE();

    return 0;
}


// References:
// https://stackoverflow.com/questions/11983875/what-does-the-thread-local-mean-in-c11
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/logging.cc#L1155
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/CMakeLists.txt#L215-L224
