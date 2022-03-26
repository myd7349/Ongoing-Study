using System;
using System.Runtime.InteropServices;

using ScottPlot;


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

        public const int Channels = 1;

        public const int TimeSliceInMilliseconds = 50;

        public const int SamplingRate = 50;

        public const int SamplesPerTimeSlice = SamplingRate * TimeSliceInMilliseconds / 1000;

        public static readonly DataGen.Electrocardiogram Generator = new DataGen.Electrocardiogram();

        private static long TotalSamples = 0;
    }
}


// References:
// [Add offset to IntPtr](https://stackoverflow.com/questions/1866236/add-offset-to-intptr)
