// 2016-04-07T14:43+08:00

using System;
using System.Runtime.InteropServices;

namespace Algorithm
{
    public partial class AlgorithmViaPInvoke : IAlgorithm
    {
        [DllImport("Kernel32.dll", EntryPoint = "RtlZeroMemory", SetLastError = false)]
        static extern void RtlZeroMemory(IntPtr dest, IntPtr size);

        public unsafe void ZeroMemory(double[] data)
        {
            fixed (double *pData = data)
            {
                RtlZeroMemory((IntPtr)pData, (IntPtr)(sizeof(double)*data.Length));
            }
        }
    }
}
