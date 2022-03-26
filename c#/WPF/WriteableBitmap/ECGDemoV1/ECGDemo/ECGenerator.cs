using System;
using System.Runtime.InteropServices;

using ScottPlot;

using Common;


namespace ECGDemo
{
    class ECGenerator
    {
        public static ulong GenerateECG(IntPtr buffer, ulong bytes, IntPtr context)
        {
            var voltage = new double[1];

            var samples = (int)bytes / sizeof(double);
            for (int i = 0; i < samples; ++i)
            {
                var elapsedSeconds = (TotalSamples++) / (double)SamplingRate;
                voltage[0] = Generator.GetVoltage(elapsedSeconds);
                Marshal.Copy(voltage, 0, IntPtr.Add(buffer, i * sizeof(double)), 1);
            }

            return bytes;
        }

        // We want a time slice in range [50ms,100ms].
        public static int CalculateBestTimeSlice()
        {
            var gcd = MathHelper.GCD((uint)SamplingRate, 1000);
            var minimumTimeSlice = 1000 / (int)gcd;

            if (minimumTimeSlice < PerfectTimeSliceInMilliseconds)
                return MathHelper.AlignUp(PerfectTimeSliceInMilliseconds, minimumTimeSlice);
            else
                return minimumTimeSlice;
        }

        public static int CalculateSamples(int timeSliceInMilliseconds)
        {
            return SamplingRate * timeSliceInMilliseconds / 1000;
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
        public const int SamplingRate = 4000;

        public static readonly DataGen.Electrocardiogram Generator = new DataGen.Electrocardiogram(60);

        private static long TotalSamples = 0;
    }
}


// References:
// [Add offset to IntPtr](https://stackoverflow.com/questions/1866236/add-offset-to-intptr)
