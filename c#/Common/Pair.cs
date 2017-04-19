// 2017-04-06T10:43:54+08:00
namespace Common
{
    public struct Pair<TFirst, TSecond>
        //where TFirst : struct
        //where TSecond : struct
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

        public TFirst First;
        public TSecond Second;
    }

    // TODO: Override `Equals` and `GetHashCode`.
}

// References:
// [Generic method with multiple constraints](http://stackoverflow.com/questions/588643/generic-method-with-multiple-constraints)
// [Constraints on Type Parameters (C# Programming Guide)](https://msdn.microsoft.com/en-us/library/d5x73970.aspx)
// [What is C# analog of C++ std::pair?](http://stackoverflow.com/questions/166089/what-is-c-sharp-analog-of-c-stdpair)
// [Is there a version of the class Tuple whose Items properties are not readonly and can be set?](http://stackoverflow.com/questions/7787994/is-there-a-version-of-the-class-tuple-whose-items-properties-are-not-readonly-an)
// [Why Tuple's items are ReadOnly?](http://stackoverflow.com/questions/3131400/why-tuples-items-are-readonly)
// CLR via C#, 3rd Edition, Ch05
