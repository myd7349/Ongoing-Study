using System;
using System.Runtime.InteropServices;

using ScottPlot;

using Common;


namespace ECGDemo
{
    class ECGenerator
    {
        public ECGenerator(double hr, int fs)
        {
            generator_ = new DataGen.Electrocardiogram(hr);
            samplingRate_ = fs;
        }

        public ulong GenerateECG(IntPtr buffer, ulong bytes, IntPtr context)
        {
            var voltage = new double[1];

            var samples = (int)bytes / sizeof(double);
            for (int i = 0; i < samples; ++i)
            {
                var elapsedSeconds = (totalSamples_++) / (double)samplingRate_;
                voltage[0] = generator_.GetVoltage(elapsedSeconds);
                Marshal.Copy(voltage, 0, IntPtr.Add(buffer, i * sizeof(double)), 1);
            }

            return bytes;
        }

        // We want a time slice in range [50ms,100ms].
        public int CalculateBestTimeSlice()
        {
            var gcd = MathHelper.GCD((uint)samplingRate_, 1000);
            var minimumTimeSlice = 1000 / (int)gcd;

            if (minimumTimeSlice < PerfectTimeSliceInMilliseconds)
                return MathHelper.AlignUp(PerfectTimeSliceInMilliseconds, minimumTimeSlice);
            else
                return minimumTimeSlice;
        }

        public int CalculateSamples(int timeSliceInMilliseconds)
        {
            return samplingRate_ * timeSliceInMilliseconds / 1000;
        }

        public const int Channels = 1;

        public const int PerfectTimeSliceInMilliseconds = 50;

        // Try this out:
        // 10
        // 50
        // 100
        // 200
        // 500
        // 1000
        // 2000
        // 4000
        // 8000
        // 16000
        private readonly int samplingRate_;
        private readonly DataGen.Electrocardiogram generator_;
        private long totalSamples_ = 0;
    }
}


// References:
// [Add offset to IntPtr](https://stackoverflow.com/questions/1866236/add-offset-to-intptr)
