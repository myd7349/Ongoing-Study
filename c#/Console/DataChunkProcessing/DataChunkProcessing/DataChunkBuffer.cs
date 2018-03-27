// 2018-03-27T09:55+08:00
namespace DataChunkProcessing
{
    using System;
    using System.Diagnostics;
    using System.Text;

    using Common;

    public class DataChunkBuffer
    {
        public DataChunkBuffer(int chunkSize, int chunksCount)
        {
            Debug.Assert(chunkSize > 0);
            Debug.Assert(chunksCount > 0);

            data = new double[chunkSize * chunksCount];
            ChunkSize = chunkSize;
            ChunksCount = chunksCount;
            startChunk = 0;
        }

        public int ChunkSize
        {
            get; private set;
        }

        public int ChunksCount
        {
            get; private set;
        }

        public void Push(double[] chunk)
        {
            Debug.Assert(chunk != null);
            Debug.Assert(chunk.Length <= ChunkSize);

            if (startChunk >= ChunksCount)
                startChunk %= ChunksCount;

            Array.Copy(chunk, 0, data, startChunk * ChunkSize, ChunkSize);

            startChunk += 1;
        }

        public unsafe double *GetChunks(int firstChunk, int chunks)
        {
            Debug.Assert(chunks <= ChunksCount);

            firstChunk %= ChunksCount;

            if (firstChunk + chunks > ChunksCount)
            {
#if false
                data = data.Rotate((ChunksCount - firstChunk) * ChunkSize);
#else
                var newData = data.Rotate((ChunksCount - firstChunk) * ChunkSize);
                Array.Copy(newData, data, data.Length);
#endif
                firstChunk = 0;
            }

            fixed (double* ptr = data)
            {
                return ptr + firstChunk * ChunkSize;
            }
        }

        public override string ToString()
        {
            var stringBuilder = new StringBuilder();

            stringBuilder.Append('[');

            stringBuilder.Append(data[0]);
            for (int i = 1; i < data.Length; ++i)
                stringBuilder.AppendFormat(", {0}", data[i]);

            stringBuilder.Append(']');

            return stringBuilder.ToString();
        }

        private double[] data;
        private int startChunk;
    }
}
