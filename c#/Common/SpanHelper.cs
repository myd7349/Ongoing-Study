#if !DOTNET35
using System.Collections.Generic;
using System;

namespace SharpEDF.Helpers
{
    internal static class SpanHelper
    {
        public static bool SequenceEqual<T>(this Span<T> source, params T[] target)
        {
            if (source.Length != target.Length)
                return false;

            for (var i = 0; i < target.Length; i++)
            {
                if (!EqualityComparer<T>.Default.Equals(source[i], target[i]))
                    return false;
            }

            return true;
        }
    }
}
#endif


// References:
// https://learn.microsoft.com/en-us/dotnet/api/system.memoryextensions.equals?view=net-6.0
