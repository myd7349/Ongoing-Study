using System;

using ScottPlot;

namespace ECGDemo
{
    class ECGenerator
    {
        public static ulong GenerateECG(IntPtr buffer, ulong bytes, IntPtr context)
        {

            return bytes;
        }

        public const int Channels = 1;

        public const int TimeSliceInMilliseconds = 50;

        public const int SamplingRate = 500;

        public const int SamplesPerTimeSlice = SamplingRate * TimeSliceInMilliseconds / 1000;

        public static readonly DataGen.Electrocardiogram Generator = new DataGen.Electrocardiogram();
    }
}
