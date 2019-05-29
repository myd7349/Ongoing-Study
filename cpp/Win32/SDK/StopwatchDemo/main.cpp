#include <iostream>

#include "../../../Stopwatch.h"


void StopWatchMemberFunctionBenchmark(int times)
{
    Stopwatch tempTimer;

    Stopwatch timer;

    timer.Start();

    for (int i = 0; i < times; ++i)
    {
        tempTimer.Restart();
        tempTimer.Stop();
        tempTimer.GetElapsedMilliseconds();
    }

    timer.Stop();

    std::cout << "Running for " << times << " times: "
        << timer.GetElapsedMilliseconds() << " ms" << std::endl;

    LONGLONG llTimes = 0;

    timer.Restart();

    while (timer.GetElapsedMilliseconds() < 1000)
    {
        tempTimer.Restart();
        tempTimer.Stop();

        llTimes += 1;
    }

    timer.Stop();

    std::cout << "Running " << llTimes << " times in "
        << timer.GetElapsedMilliseconds() << " ms.\n";
}


void Test01()
{
    StopWatchMemberFunctionBenchmark(10000000);
}


void Test02()
{
    for (int i = 0; i < 5; ++i)
    {
        Stopwatch stopWatch;
        stopWatch.Start();

        Sleep(i * 1000);
        
        stopWatch.Stop();
        std::cout << stopWatch.GetElapsedMilliseconds() << std::endl;
    }
}


int main()
{
    Test01();
    Test02();

    return 0;
}
