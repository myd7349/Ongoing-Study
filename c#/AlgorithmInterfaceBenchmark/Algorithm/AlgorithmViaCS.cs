// 2016-04-07T14:41+08:00

using System;

namespace Algorithm
{
    public sealed class AlgorithmViaCS : IAlgorithm
    {
        public void CopyArray(int[] destArray, int[] srcArray)
        {
            int length = Math.Min(destArray.Length, srcArray.Length);
            for (int i = 0; i < length; ++i)
                destArray[i] = srcArray[i];
        }

        public void ZeroArray(double[] data)
        {

            for (int i = 0; i < data.Length; ++i)
                data[i] = 0;

            //System.Array.Clear(data, 0, data.Length);
        }
    }
}
