// 2016-05-30T15:17+08:00
using System;

namespace Common
{
    using BYTE = Byte;
    using WORD = UInt16;
    using DWORD = UInt32;
    using DWORD_PTR = UInt32;

    public static class IntegerHelper
    {
        public static byte LOBYTE(BYTE w)
        {
            return w;
        }

        public static byte LOBYTE(WORD w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }

        public static byte LOBYTE(DWORD w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }

        public static byte LOBYTE(UInt64 w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }

        public static byte LOBYTE(Int16 w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }

        public static byte LOBYTE(Int32 w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }

        public static byte LOBYTE(Int64 w)
        {
            return ((BYTE)(((DWORD_PTR)(w)) & 0xff)); // WinDef.h:203
        }
    }
}
