namespace ByteSwapBenchmark
{
    public static class BitOperations
    {
        public static uint RotateLeft(uint value, int offset)
            => (value << offset) | (value >> (32 - offset));

        public static ulong RotateLeft(ulong value, int offset)
            => (value << offset) | (value >> (64 - offset));

        public static uint RotateRight(uint value, int offset)
            => (value >> offset) | (value << (32 - offset));

        public static ulong RotateRight(ulong value, int offset)
            => (value >> offset) | (value << (64 - offset));
    }
}


// References:
// https://github.com/dotnet/coreclr/blob/5068bb8820ebd1820e70aea091bf56b19ae84f13/src/System.Private.CoreLib/shared/System/Numerics/BitOperations.cs#L329-L369
