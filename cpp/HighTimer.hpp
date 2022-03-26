// Stopwatch.h/cpp is too complicated.
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class HighTimer
{
public:
    static LONGLONG GetTimestamp()
    {
        LARGE_INTEGER current;

        if (QueryPerformanceCounter(&current))
            return current.QuadPart;
        else
            return 0;
    }

    static LONGLONG TimestampAsMicroseconds(LONGLONG stamp)
    {
        LARGE_INTEGER frequency;

        if (QueryPerformanceFrequency(&frequency))
            return static_cast<LONGLONG>(stamp * 1.0e6 / frequency.QuadPart);
        else
            return 0;
    }

    static LONGLONG TimestampAsMilliseconds(LONGLONG stamp)
    {
        return TimestampAsMicroseconds(stamp) / 1000;
    }

    HighTimer()
        : start_time_(0), started_(false)
    {
    }

    void Restart()
    {
        start_time_ = GetTimestamp();
        started_ = start_time_ != 0;
    }

    LONGLONG GetElapsedMicroseconds()
    {
        if (started_)
            return TimestampAsMicroseconds(GetTimestamp() - start_time_);
        else
            return 0;
    }

private:
    LONGLONG start_time_;
    bool started_;
};
