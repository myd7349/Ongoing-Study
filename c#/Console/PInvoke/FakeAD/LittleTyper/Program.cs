//#define I_FAILED

using System;
using System.Runtime.InteropServices;
using System.Text;

using Common;
using FakeAD;

namespace LittleTyper
{
    class Typer
    {
        public static byte[] Hello = Encoding.ASCII.GetBytes("Hello, world!\nGround control to major Tom.\n");

#if I_FAILED
        public static ulong TypeIn(IntPtr buffer, ulong bytes, IntPtr context)
        {
            var pinnedObject = GCHandle.FromIntPtr(context).Target;
            var cursor = (int)pinnedObject;
            for (uint i = 0; i < bytes; ++i)
            {
                Marshal.WriteByte(buffer, (int)i, Hello[cursor++]);
                if (cursor == Hello.Length)
                    return 0;

                Marshal.WriteInt32(context, cursor);
            }

            return bytes;
        }
#else
        public static int Position = 0;

        public static ulong TypeIn(IntPtr buffer, ulong bytes, IntPtr context)
        {
            for (uint i = 0; i < bytes; ++i)
            {
                if (Position >= Hello.Length)
                    return 0;

                Marshal.WriteByte(buffer, (int)i, Hello[Position++]);
            }

            return bytes;
        }
#endif
    }

    class Program
    {
        const uint CharsPerSecond = 10;

        static void Main(string[] args)
        {
            Console.WriteLine($"sizeof(int): {sizeof(int)}");
            Console.WriteLine($"sizeof(long): {sizeof(long)}");
            Console.WriteLine($"{FakeADWrapper.ErrorToString(Error.Success)}");

#if I_FAILED
            int cursor = 0;
            var pinnedCursor = new PinnedObject(cursor);
            var pinnedCursorOpaqueHandle = pinnedCursor.ToIntPtr();
#endif
            var fakeAd = new FakeADWrapper(
                bytesPerSecond: CharsPerSecond,
                timeSliceInMilliseconds: 100,
                timeoutSliceCount: 3,
                port: 7373,
                callback: Typer.TypeIn,
#if I_FAILED
#if false
                context: pinnedCursor);
#elif false
                context: pinnedCursor.ToIntPtr());
#else
                context: pinnedCursorOpaqueHandle);
#endif
#else
                context: IntPtr.Zero);
#endif

            var buffer = new UnmanagedBuffer(sizeof(byte));
            while (fakeAd.Read(buffer, sizeof(byte)) == sizeof(byte))
                Console.Write((char)buffer.Read<byte>());

#if I_FAILED
            Console.WriteLine($"Cursor: {cursor}");
#endif

            Console.ReadKey();
        }
    }
}


// References:
// [C# - How To Convert Object To IntPtr And Back?](https://stackoverflow.com/questions/17339928/c-sharp-how-to-convert-object-to-intptr-and-back)
