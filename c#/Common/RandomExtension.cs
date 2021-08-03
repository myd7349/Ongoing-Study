namespace Common
{
    using System;
    using System.Linq;

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

        public static string RandomString(this Random random, int length,
            string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
        {
            return new string(Enumerable.Repeat(chars, length)
              .Select(s => s[random.Next(s.Length)]).ToArray());
        }
    }
}


// References:
// https://stackoverflow.com/questions/6651554/random-number-in-long-range-is-this-the-way
// [How can I generate random alphanumeric strings?](https://stackoverflow.com/questions/1344221/how-can-i-generate-random-alphanumeric-strings)
