// 2016-04-07T14:41+08:00

using System;

namespace Algorithm
{
    public sealed class AlgorithmViaCS : IAlgorithm
    {
        public void ZeroMemory(double[] data)
        {

            for (int i = 0; i < data.Length; ++i)
                data[i] = 0;

            //System.Array.Clear(data, 0, data.Length);
        }
    }
}
