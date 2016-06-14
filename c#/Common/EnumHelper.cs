// 2016-06-02T17:35+08:00
using System;
using System.Collections.Generic;

namespace Common
{
    public sealed class EnumHelper<T> where T : struct
    {
        static EnumHelper()
        {
            EnumNamesDict = new Dictionary<T, string>();
            foreach (var value in Enum.GetValues(typeof(T)))
                EnumNamesDict[(T)value] = value.ToString();
        }

        public static readonly Dictionary<T, string> EnumNamesDict;
    }
}
