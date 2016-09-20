// 2016-09-20T12:03+08:00
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include "PetersonAlgorithm.h"

int Money;

inline void EarnOneDollar()
{
    ++Money;
}

void WorkerRoutine(int workerId)
{
    assert(workerId == 0 || workerId == 1);

    for (int i = 0; i < 100000; ++i)
    {
        EnterRegion(workerId);
        EarnOneDollar();
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        LeaveRegion(workerId);
    }
}

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        std::thread worker0(WorkerRoutine, 0);
        std::thread worker1(WorkerRoutine, 1);

        worker0.join();
        worker1.join();

        std::cout << "How many dollars? " << Money << std::endl;

        Money = 0;
    }

    return 0;
}

// References:
// Modern Operating System 4th Edition P125
// https://en.wikipedia.org/wiki/Peterson%27s_algorithm
