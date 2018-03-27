namespace DataChunkProcessing
{
    using System;

    using Common;

    class Program
    {
        static unsafe void Main(string[] args)
        {
            var chunks = new DataChunkBuffer(2, 10);

            for (int i = 0; i < 10; ++i)
            {
                chunks.Push(new double[] { i, i * i });
                Console.WriteLine(chunks);
            }

            Console.WriteLine("----------------------------");

            for (int i = 0; i < 10; ++i)
            {
                Console.WriteLine(chunks);
                var ptr = chunks.GetChunks(i, 3);
                DataChunkProcessingNative.ProcessNative((IntPtr)ptr, (uint)(3 * chunks.ChunkSize));
            }

            Util.Pause();
        }
    }
}
