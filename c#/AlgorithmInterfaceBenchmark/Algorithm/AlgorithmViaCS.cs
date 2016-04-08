// 2016-04-07T14:41+08:00

using System;

namespace Algorithm
{
    public sealed class AlgorithmViaCS : IAlgorithm
    {
        public AlgorithmViaCS(int length, bool useDIYVersion)
        {
            filter = new Filter(length);

            this.useDIYVersion = useDIYVersion;
            copyArray = useDIYVersion ? CopyArrayDIY : (Action<int[], int[], int>)Array.Copy;
            zeroArray = useDIYVersion ? ZeroArrayDIY : (Action<double[], int, int>)Array.Clear;
        }

        public void CopyArray(int[] destArray, int[] srcArray)
        {
            copyArray(srcArray, destArray, Math.Min(destArray.Length, srcArray.Length));
        }

        public double MagicFilter(double v)
        {
            return filter.Run(v);
        }

        public void ZeroArray(double[] data)
        {
            zeroArray(data, 0, data.Length);
        }

        public override string ToString()
        {
            //return GetType().Name + (useDIYVersion ? "<DIY>" : "");
            return base.ToString() + (useDIYVersion ? "<DIY>" : "");
        }

        private Action<int[], int[], int> copyArray;
        private Action<double[], int, int> zeroArray;
        private bool useDIYVersion;
        private Filter filter;

        private static void CopyArrayDIY(int[] srcArray, int[] destArray, int length)
        {
            for (int i = 0; i < length; ++i)
                destArray[i] = srcArray[i];
        }

        private static void ZeroArrayDIY(double[] array, int index, int length)
        {
            int endIndex = Math.Min(index + length, array.Length);
            for (int i = index; i < endIndex; ++i)
                array[i] = 0;
        }
    }

    internal sealed class Filter
    {
        public Filter(int bufferLength)
        {
            buffer = new double[bufferLength];
            sortedBuffer = new double[bufferLength];
        }

        public double Run(double v)
        {
            for (int i = 1; i < buffer.Length; ++i)
                buffer[i - 1] = buffer[i];
            buffer[buffer.Length - 1] = v;

            Array.Copy(buffer, sortedBuffer, buffer.Length);
            Array.Sort(sortedBuffer);

            return sortedBuffer[sortedBuffer.Length / 2];
        }

        private double[] buffer;
        private double[] sortedBuffer;
    }
}
