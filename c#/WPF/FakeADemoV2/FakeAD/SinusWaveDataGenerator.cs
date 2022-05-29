namespace FakeAD
{
    using System;

    public class SinusWaveDataGenerator : IDataGenerator
    {
        public SinusWaveDataGenerator(double period, double samplingRate)
        {
            if (period <= 0.0)
                throw new ArgumentException("Invalid period");

            if (samplingRate <= 0.0)
                throw new ArgumentException("Invalid sampling rate");

            w_ = 2 * Math.PI / period;
            SamplingRate_ = samplingRate;
        }

        public int Samples { get; private set; } = 0;

        public double Next()
        {
            return Math.Sin(w_ * (Samples++) / SamplingRate_);
        }

        private readonly double w_;
        private double SamplingRate_ { get; }
    }
}

/*
using System;
using System.Threading;

public class SineSignalGenerator : ISignalGenerator
{
    public int PeriodInMilliseconds
    {
        get
        {
            var w = Interlocked.CompareExchange(ref w_, 0, 0);
            if (w == 0)
                return 0;

            var period = 2 * Math.PI / w;
            return (int)(period * 1000);
        }

        set
        {
            if (value <= 0)
                throw new ArgumentOutOfRangeException(nameof(PeriodInMilliseconds));

            var w = 2 * Math.PI * 1000 / value;
            Interlocked.Exchange(ref w_, w);
        }
    }

    public int AmplitudeInMicrovolts { get; set; }

    public double GetVoltage(double elapsedSeconds)
    {
        var w = Interlocked.CompareExchange(ref w_, 0, 0);
        if (w <= 0)
            throw new ArgumentOutOfRangeException(nameof(PeriodInMilliseconds));

        var startTimePointInSeconds = Interlocked.CompareExchange(ref startTimePointInSeconds_, elapsedSeconds, 0);
        return AmplitudeInMicrovolts * Math.Sin(w * (elapsedSeconds - startTimePointInSeconds));
    }

    public void Reset()
    {
        Interlocked.Exchange(ref startTimePointInSeconds_, 0);
    }

    private double w_;
    private double startTimePointInSeconds_;
}

// References:
// https://github.com/ScottPlot/ScottPlot/blob/main/src/ScottPlot4/ScottPlot/DataGen.cs
// [Is reading a double not thread-safe?](https://stackoverflow.com/questions/3676808/is-reading-a-double-not-thread-safe)
*/
