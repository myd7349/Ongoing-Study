// 2016-04-07T10:07+08:00

using System;

namespace Algorithm
{
    public sealed class AlgorithmViaUnsafeCode : IAlgorithm
    {
        public unsafe void ZeroMemory(double[] data)
        {
            fixed (double *p = data)
            {
                for (int i = 0; i < data.Length; ++i)
                    p[i] = 0;
            }
        }
    }
}
