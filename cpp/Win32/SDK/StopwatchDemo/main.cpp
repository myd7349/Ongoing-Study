#include <iostream>

#include "../../../Stopwatch.h"


int main()
{
    for (int i = 0; i < 5; ++i)
    {
        Stopwatch stopWatch;
        stopWatch.Start();

        Sleep(i * 1000);
        
        stopWatch.Stop();
        std::cout << stopWatch.GetElapsedMilliseconds() << std::endl;
    }

    return 0;
}
