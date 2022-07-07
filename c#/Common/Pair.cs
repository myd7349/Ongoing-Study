// 2017-04-06T10:43:54+08:00

// Another Pair implementation by wj32:
// https://github.com/wj32/Wj.Math/blob/master/Wj.Math/Pair.cs
// System.Collections.Generic.KeyValuePair<TKey,TValue>
// [Pair Class](https://docs.microsoft.com/en-us/dotnet/api/system.web.ui.pair?view=netframework-4.8)
// [How to modify a KeyValuePair value?](https://stackoverflow.com/questions/13454721/how-to-modify-a-keyvaluepair-value)

namespace Common
{
    using System;

    public struct Pair<TFirst, TSecond> : IEquatable<Pair<TFirst, TSecond>>
    {
        public Pair(Pair<TFirst, TSecond> other)
        {
            First = other.First;
            Second = other.Second;
        }

        public Pair(TFirst first = default(TFirst), TSecond second = default(TSecond))
        {
            First = first;
            Second = second;
        }

        //public override int GetHashCode()
        //{
        //    return HashHelpers.CombineHash(First.GetHashCode(), Second.GetHashCode());
        //}

        public void Clear()
        {
            First = default(TFirst);
            Second = default(TSecond);
        }

        public bool Equals(Pair<TFirst, TSecond> other)
        {
            return First.Equals(other.First) && Second.Equals(other.Second);
        }

        public TFirst First;
        public TSecond Second;

        public static readonly Pair<TFirst, TSecond> Empty = new Pair<TFirst, TSecond>();

        public static Pair<T1, T2> Create<T1, T2>(T1 first = default(T1), T2 second = default(T2))
        {
            return new Pair<T1, T2>(first, second);
        }
    }
}

// References:
// [Generic method with multiple constraints](http://stackoverflow.com/questions/588643/generic-method-with-multiple-constraints)
// [Constraints on Type Parameters (C# Programming Guide)](https://msdn.microsoft.com/en-us/library/d5x73970.aspx)
// [What is C# analog of C++ std::pair?](http://stackoverflow.com/questions/166089/what-is-c-sharp-analog-of-c-stdpair)
// [Is there a version of the class Tuple whose Items properties are not readonly and can be set?](http://stackoverflow.com/questions/7787994/is-there-a-version-of-the-class-tuple-whose-items-properties-are-not-readonly-an)
// [Why Tuple's items are ReadOnly?](http://stackoverflow.com/questions/3131400/why-tuples-items-are-readonly)
// CLR via C#, 3rd Edition, Ch05
// https://github.com/JimBobSquarePants/ImageProcessor/blob/release/3.0.0/src/ImageProcessor/Bgra32.cs
// [Is there a version of the class Tuple whose Items properties are not readonly and can be set?](https://stackoverflow.com/questions/7787994/is-there-a-version-of-the-class-tuple-whose-items-properties-are-not-readonly-an)
// > Implementing GetHashCode() for a mutable type? - Risky that.
// [Is there a complete IEquatable implementation reference?](https://stackoverflow.com/questions/1307493/is-there-a-complete-iequatable-implementation-reference)
