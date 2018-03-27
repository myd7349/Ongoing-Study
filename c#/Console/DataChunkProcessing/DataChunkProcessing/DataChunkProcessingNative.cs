namespace DataChunkProcessing
{
    using System;
    using System.Runtime.InteropServices;

    public static class DataChunkProcessingNative
    {
        [DllImport("DataChunkProcessingNative", EntryPoint = "ProcessDataChunk")]
        public static extern void Process(double[] chunk, uint size);

#if false
        [DllImport("DataChunkProcessingNative", EntryPoint = "ProcessDataChunk")]
        public static unsafe extern void ProcessNative(double *chunk, uint size);
#else
        [DllImport("DataChunkProcessingNative", EntryPoint = "ProcessDataChunk", CallingConvention = CallingConvention.Cdecl)]
        public static unsafe extern void ProcessNative(IntPtr chunk, uint size);
#endif
    }
}
