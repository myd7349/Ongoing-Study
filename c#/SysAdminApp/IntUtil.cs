using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SysAdminApp
{
    public sealed class IntUtil
    {
        public static void SetBits(ref Int32 value, Int32 bits)
        {
            value |= bits;
        }

        public static void ClearBits(ref Int32 value, Int32 bits)
        {
            value &= ~bits;
        }

        public static void TriggleBits(ref Int32 value, Int32 bits, bool bSet)
        {
            if (bSet)
                SetBits(ref value, bits);
            else
                ClearBits(ref value, bits);
        }

        public static bool IsBitsSet(Int32 value, Int32 bits)
        {
            return (value & bits) != 0;
        }
    }
}
