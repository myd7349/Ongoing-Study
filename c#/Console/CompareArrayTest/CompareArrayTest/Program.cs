// 2016-06-15T11:07+08:00
using System;
using System.Diagnostics;
using System.IO;

using Common;

namespace CompareArrayTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var bytes = Properties.Resources.DeputyWave;

            int dataLength = bytes.Length / sizeof(double);
            double[] data1 = new double[dataLength];
            double[] data2 = data1.Clone() as double[];

            // 1.
            Buffer.BlockCopy(bytes, 0, data1, 0, bytes.Length);

            // 2.
            using (var stream = new MemoryStream(bytes))
            using (var reader = new BinaryReader(stream))
            {
                for (int i = 0; i < data2.Length; ++i)
                    data2[i] = reader.ReadDouble();
            }

            Debug.Assert(data1.EqualTo(data2));

            Util.Pause();
        }
    }
}

// References:
// [How do I convert byte[] to stream in C#?](http://stackoverflow.com/questions/4736155/how-do-i-convert-byte-to-stream-in-c)