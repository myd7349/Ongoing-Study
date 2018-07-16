#include "Stopwatch.h"


Stopwatch::InternalData::InternalData()
{
    if (QueryPerformanceFrequency(&Frequency))
    {
        IsHighResolution = true;
        TickFrequency = TicksPerSecond / Frequency.QuadPart;
    }
    else
    {
        IsHighResolution = false;
        Frequency.QuadPart = TicksPerSecond;
        TickFrequency = 1;
    }
}


Stopwatch::InternalData Stopwatch::internalData_;



