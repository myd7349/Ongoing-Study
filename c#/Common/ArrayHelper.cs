// 2016-06-15T11:12+08:00
using System;
using System.Collections.Generic;
using System.Linq;


namespace Common
{
    public static class ArrayHelper
    {
        [Obsolete("Use Array.Fill instead.")]
        public static void Fill<T>(this T[] array, T value)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            for (int i = 0; i < array.Length; i++)
                array[i] = value;
        }

        public static void Fill<T>(this T[] array, int offset, int count, T value)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            ValidateArray(array, offset, count);

            for (int i = 0; i < count; i++)
                array[offset + i] = value;
        }

        public static void Fill<T>(this T[,] array, T value)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            for (int i = 0; i < array.GetLength(0); ++i)
            {
                for (int j = 0; j < array.GetLength(1); ++j)
                    array[i, j] = value;
            }
        }

        public static bool EqualTo<T>(this T[] lhs, T[] rhs)
        {
            if (ReferenceEquals(lhs, rhs))
                return true;

            if (lhs == null || rhs == null)
                return false;

            if (lhs.Length != rhs.Length)
                return false;

            EqualityComparer<T> comparer = EqualityComparer<T>.Default;
            for (int i = 0; i < lhs.Length; i++)
            {
                if (!comparer.Equals(lhs[i], rhs[i]))
                    return false;
            }

            return true;
        }

        public static bool SequenceEqual<T>(this T[] source, int sourceIndex, T[] target, int targetIndex, int count)
        {
            ValidateArray(source, sourceIndex, count);
            ValidateArray(target, targetIndex, count);

            for (var i = 0; i < count; i++)
            {
                if (!EqualityComparer<T>.Default.Equals(source[sourceIndex + i], target[targetIndex + i]))
                    return false;
            }

            return true;
        }

        public static bool SequenceEqual<T>(this T[] source, int sourceIndex, params T[] target)
        {
            return source.SequenceEqual(sourceIndex, target, 0, target.Length);
        }

        public static T[] Rotate<T>(this T[] array, int rotate)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            if (rotate > 0)
            {
                rotate = array.Length - rotate % array.Length;
            }
            else if (rotate < 0)
            {
                rotate = -rotate;
                rotate %= array.Length;
            }

            if (rotate == 0)
                return (T[])array.Clone();

            return array.Skip(rotate).Concat(array.Take(rotate)).ToArray();
        }

        // https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/NetworkStream.cs
        // > ValidateBufferArguments(buffer, offset, count);
        public static void ValidateArray<T>(T[] array, int offset, int count)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            if (offset < 0 || offset >= array.Length)
                throw new ArgumentOutOfRangeException("offset");

            if (count <= 0 || offset + count > array.Length)
                throw new ArgumentOutOfRangeException("count");
        }
    }
}

// References:
// [Comparing arrays in C#](http://stackoverflow.com/questions/713341/comparing-arrays-in-c-sharp)
// [Easiest way to Rotate a List in c#](https://stackoverflow.com/questions/9948202/easiest-way-to-rotate-a-list-in-c-sharp)
// C# 6.0 in a Nutshell, P298
// > Framework 4.0 introduced one for the purpose of comparing elements in arrays or tuples
//   which you can access via the StructuralComparisons type.
// [StructuralComparisons for arrays](https://stackoverflow.com/questions/32095508/structuralcomparisons-for-arrays)
// [Array.Fill Method](https://docs.microsoft.com/en-us/dotnet/api/system.array.fill?view=net-5.0)
// [How to populate/instantiate a C# array with a single value?](https://stackoverflow.com/questions/1014005/how-to-populate-instantiate-a-c-sharp-array-with-a-single-value)
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/Infrastructure/ReferenceEqualityComparer.cs
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/Infrastructure/EnumerableExtensions.cs
// https://docs.microsoft.com/en-us/dotnet/api/system.linq.enumerable.sequenceequal?view=net-5.0
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/ParserResult.cs
// [Comparing two byte arrays in .NET](https://stackoverflow.com/questions/43289/comparing-two-byte-arrays-in-net)
