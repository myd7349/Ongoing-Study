// 2018-03-21T09:29+08:00
#include <iostream>
#include <thread>
#include <vector>

#include "semaphore.hpp"


struct Args
{
    Args(int avail) : count(0), semaphore(1) {}

    int count;
    Semaphore semaphore;
};


void Run(Args &args)
{
    args.semaphore.Acquire();
    args.count += 1;
    args.semaphore.Release();
}

int main()
{
    Args args(1);

    const int THREAD_COUNT = 50;
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; ++i)
        threads.push_back(std::thread(Run, std::ref(args)));

    for (auto &thread : threads)
        thread.join();

    std::cout << args.count << std::endl;

    return 0;
}

// References:
// https://stackoverflow.com/questions/42269611/non-blocking-semaphores-in-c11
