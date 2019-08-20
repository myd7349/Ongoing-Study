namespace Common
{
    using System;

    public static class RandomExtension
    {
        public static short RandomShort(this Random rnd)
        {
            return (short)rnd.Next(short.MinValue, short.MaxValue);
        }

        public static ushort RandomUShort(this Random rnd)
        {
            return (ushort)rnd.Next(ushort.MinValue, ushort.MaxValue);
        }

        public static long RandomLong(this Random rnd)
        {
            return (long)rnd.RandomULong();
        }

        public static ulong RandomULong(this Random rnd)
        {
            byte[] buffer = new byte[8];
            rnd.NextBytes(buffer);
            return BitConverter.ToUInt64(buffer, 0);
        }
    }
}


// References:
// https://stackoverflow.com/questions/6651554/random-number-in-long-range-is-this-the-way
