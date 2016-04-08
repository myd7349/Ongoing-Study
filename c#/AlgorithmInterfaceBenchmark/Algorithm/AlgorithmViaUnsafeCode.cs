// 2016-04-07T10:07+08:00

using System;

namespace Algorithm
{
    public sealed class AlgorithmViaUnsafeCode : IAlgorithm
    {
        public AlgorithmViaUnsafeCode(int bufferLength)
        {
            filter = new Filter(bufferLength);
        }

        public unsafe void CopyArray(int[] destArray, int[] srcArray)
        {
            int length = Math.Min(destArray.Length, srcArray.Length);
            fixed (int* dest = destArray)
            {
                fixed (int* src = srcArray)
                {
                    int* p = dest;
                    int* end = p + length;
                    int* q = src;
                    while (p < end)
                        *p++ = *q++;
                }
            }
        }

        public double MagicFilter(double v)
        {
            return filter.Run(v);
        }

        public unsafe void ZeroArray(double[] data)
        {
            fixed (double* p = data)
            {
                double* pos = p;
                double* end = p + data.Length;
                while (pos < end)
                    *pos++ = 0;
            }
        }

        private Filter filter;
    }
}
