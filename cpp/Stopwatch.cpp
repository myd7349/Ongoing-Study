#include "Stopwatch.h"


Stopwatch::InternalData::InternalData()
{
    if (QueryPerformanceFrequency(&Frequency))
    {
        IsHighResolution = true;
        TickFrequency = static_cast<long double>(TicksPerSecond) / Frequency.QuadPart;
    }
    else
    {
        IsHighResolution = false;
        Frequency.QuadPart = TicksPerSecond;
        TickFrequency = 1.0;
    }
}


Stopwatch::InternalData Stopwatch::internalData_;



