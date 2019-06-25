#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


class Stopwatch
{
public:
    static LONGLONG GetFrequency()
    {
        return internalData_.Frequency.QuadPart;
    }

    static bool IsHighResolution()
    {
        return internalData_.IsHighResolution;
    }

    static LONGLONG GetTimestamp()
    {
        if (IsHighResolution())
        {
            LARGE_INTEGER performanceCount;
            QueryPerformanceCounter(&performanceCount);
            return performanceCount.QuadPart;
        }
        else
        {
            return GetTickCount() * TicksPerMillisecond;
        }
    }

    Stopwatch()
    {
        Reset();
    }

    void Start()
    {
        // Calling start on a running Stopwatch is a no-op.
        if (!isRunning_)
        {
            startTimestamp_ = GetTimestamp();
            isRunning_ = true;
        }
    }

    void Stop()
    {
        // Calling stop on a stopped Stopwatch is a no-op.
        if (isRunning_)
        {
            LONGLONG endTimestamp = GetTimestamp();
            LONGLONG elapsedThisPeriod = endTimestamp - startTimestamp_;
            elapsed_ += elapsedThisPeriod;
            isRunning_ = false;
            
            if (elapsed_ < 0)
            {
                // When measuring small time periods the StopWatch.Elapsed* 
                // properties can return negative values.  This is due to 
                // bugs in the basic input/output system (BIOS) or the hardware
                // abstraction layer (HAL) on machines with variable-speed CPUs
                // (e.g. Intel SpeedStep).

                elapsed_ = 0;
            }
        }
    }

    void Reset()
    {
        elapsed_ = 0;
        isRunning_ = false;
        startTimestamp_ = 0;
    }

    void Restart()
    {
        elapsed_ = 0;
        startTimestamp_ = GetTimestamp();
        isRunning_ = true;
    }

    bool IsRunning() const
    {
        return isRunning_;
    }

    //GetElapsed()

    LONGLONG GetElapsedMilliseconds() const
    {
        return GetElapsedDateTimeTicks() / TicksPerMillisecond;
    }

    LONGLONG GetElapsedTicks() const
    {
        return GetRawElapsedTicks();
    }

    LONGLONG GetRawElapsedTicks() const
    {
        LONGLONG timeElapsed = elapsed_;
        
        if (isRunning_)
        {
            LONGLONG currentTimestamp = GetTimestamp();
            LONGLONG elapsedUntilNow = currentTimestamp - startTimestamp_;
            timeElapsed += elapsedUntilNow;
        }

        return timeElapsed;
    }

    LONGLONG GetElapsedDateTimeTicks() const
    {
        LONGLONG rawTicks = GetRawElapsedTicks();

        if (IsHighResolution())
        {
            long double dticks = static_cast<long double>(rawTicks);
            dticks *= internalData_.TickFrequency;
            return static_cast<LONGLONG>(dticks);
        }
        else
        {
            return rawTicks;
        }
    }

private:
    struct InternalData
    {
        InternalData();

        LARGE_INTEGER Frequency;
        bool IsHighResolution;
        long double TickFrequency;
    };

    static InternalData internalData_;

    // coreclr\src\mscorlib\shared\System\DateTime.cs
    /*
        // Returns the tick count for this DateTime. The returned value is
        // the number of 100-nanosecond intervals that have elapsed since 1/1/0001
        // 12:00am.
        //
        public long Ticks
    */
    // 1ms = 1000000ns = 1000000/100ticks
    static const long TicksPerMillisecond = 10000;
    static const long TicksPerSecond = TicksPerMillisecond * 1000;

    LONGLONG elapsed_;
    LONGLONG startTimestamp_;
    bool isRunning_;
};


// References:
// corefx\src\System.Runtime.Extensions\src\System\Diagnostics\Stopwatch.cs
// https://www.zhihu.com/question/266754507
// https://github.com/miloyip/nativejson-benchmark/blob/master/src/timer.h
// https://docs.microsoft.com/zh-cn/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps
// https://currentmillis.com/
// https://gamedev.stackexchange.com/questions/26759/best-way-to-get-elapsed-time-in-miliseconds-in-windows
// https://stackoverflow.com/questions/3729169/how-can-i-get-the-windows-system-time-with-millisecond-resolution
// https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
// https://www.linuxquestions.org/questions/programming-9/how-to-convert-tsc-cpu-cycles-into-seconds-in-c-833190/
// https://msdn.microsoft.com/en-us/library/twchhe95.aspx
