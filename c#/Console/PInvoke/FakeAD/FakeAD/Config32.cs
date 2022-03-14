using System;
using System.Runtime.InteropServices;

namespace FakeAD
{
    [StructLayout(LayoutKind.Explicit)]
    internal struct Config32
    {
        [FieldOffset(0)]
        public uint BytesPerSecond;

        [FieldOffset(4)]
        public uint TimeSliceInMilliseconds;

        [FieldOffset(8)]
        public uint TimeoutSliceCount;

        [FieldOffset(12)]
        public ushort Port;

        [FieldOffset(14)]
        public ushort WSAStartup;

        [FieldOffset(16)]
        [MarshalAs(UnmanagedType.FunctionPtr)]
        public FakeADCallback32 Callback;

        [FieldOffset(20)]
        public IntPtr Context;
    }
}


// References:
// [PInvoke a struct pointer to get the data](https://stackoverflow.com/questions/25892205/pinvoke-a-struct-pointer-to-get-the-data)
