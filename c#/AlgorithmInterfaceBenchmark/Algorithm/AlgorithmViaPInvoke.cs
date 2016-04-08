// 2016-04-07T14:43+08:00

using System;
using System.Runtime.InteropServices;

namespace Algorithm
{
    public partial class AlgorithmViaPInvoke : IAlgorithm
    {
        [DllImport("Kernel32.dll", EntryPoint = "CopyMemory", SetLastError = false)]
        static extern void CopyMemory(IntPtr dest, IntPtr src, uint size);

        [DllImport("Kernel32.dll", EntryPoint = "RtlZeroMemory", SetLastError = false)]
        static extern void RtlZeroMemory(IntPtr dest, uint size);

        public AlgorithmViaPInvoke(int bufferLength)
        {
            filter = new global::Filter(bufferLength);
        }

        public unsafe void CopyArray(int[] destArray, int[] srcArray)
        {
            int length = Math.Min(destArray.Length, srcArray.Length);
            fixed (int* dest = destArray)
            {
                fixed (int* src = srcArray)
                {
                    CopyMemory((IntPtr)dest, (IntPtr)src, (uint)(sizeof(int) * length));
                }
            }
        }

        public double MagicFilter(double v)
        {
            return filter.Run(v);
        }

        public unsafe void ZeroArray(double[] data)
        {
            fixed (double* pData = data)
            {
                RtlZeroMemory((IntPtr)pData, (uint)(sizeof(double) * data.Length));
            }
        }

        private global::Filter filter;
    }
}
