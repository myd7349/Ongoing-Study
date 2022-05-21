using System;

namespace Common
{
    public static class TupleExtension
    {
        public static Tuple<T1> WithItem1<T1>(this Tuple<T1> tuple, T1 item1)
        {
            return Tuple.Create(item1);
        }

        public static Tuple<T1, T2> WithItem2<T1, T2>(this Tuple<T1> tuple, T2 item2)
        {
            return Tuple.Create(tuple.Item1, item2);
        }

        public static Tuple<T1, T2> WithItem1<T1, T2>(this Tuple<T1, T2> tuple, T1 item1)
        {
            return Tuple.Create(item1, tuple.Item2);
        }

        public static Tuple<T1, T2> WithItem2<T1, T2>(this Tuple<T1, T2> tuple, T2 item2)
        {
            return Tuple.Create(tuple.Item1, item2);
        }

        public static Tuple<T1, T2, T3> WithItem3<T1, T2, T3>(this Tuple<T1, T2> tuple, T3 item3)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, item3);
        }

        public static Tuple<T1, T2, T3> WithItem1<T1, T2, T3>(this Tuple<T1, T2, T3> tuple, T1 item1)
        {
            return Tuple.Create(item1, tuple.Item2, tuple.Item3);
        }

        public static Tuple<T1, T2, T3> WithItem2<T1, T2, T3>(this Tuple<T1, T2, T3> tuple, T2 item2)
        {
            return Tuple.Create(tuple.Item1, item2, tuple.Item3);
        }

        public static Tuple<T1, T2, T3> WithItem3<T1, T2, T3>(this Tuple<T1, T2, T3> tuple, T3 item3)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, item3);
        }

        public static Tuple<T1, T2, T3, T4> WithItem4<T1, T2, T3, T4>(this Tuple<T1, T2, T3> tuple, T4 item4)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, tuple.Item3, item4);
        }

        public static Tuple<T1, T2, T3, T4> WithItem1<T1, T2, T3, T4>(this Tuple<T1, T2, T3, T4> tuple, T1 item1)
        {
            return Tuple.Create(item1, tuple.Item2, tuple.Item3, tuple.Item4);
        }

        public static Tuple<T1, T2, T3, T4> WithItem2<T1, T2, T3, T4>(this Tuple<T1, T2, T3, T4> tuple, T2 item2)
        {
            return Tuple.Create(tuple.Item1, item2, tuple.Item3, tuple.Item4);
        }

        public static Tuple<T1, T2, T3, T4> WithItem3<T1, T2, T3, T4>(this Tuple<T1, T2, T3, T4> tuple, T3 item3)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, item3, tuple.Item4);
        }

        public static Tuple<T1, T2, T3, T4> WithItem4<T1, T2, T3, T4>(this Tuple<T1, T2, T3, T4> tuple, T4 item4)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, tuple.Item3, item4);
        }

        public static Tuple<T1, T2, T3, T4, T5> WithItem5<T1, T2, T3, T4, T5>(this Tuple<T1, T2, T3, T4> tuple, T5 item5)
        {
            return Tuple.Create(tuple.Item1, tuple.Item2, tuple.Item3, tuple.Item4, item5);
        }
    }
}


// References:
// [Is there a version of the class Tuple whose Items properties are not readonly and can be set?](https://stackoverflow.com/questions/7787994/is-there-a-version-of-the-class-tuple-whose-items-properties-are-not-readonly-an)
// [Class inheritance: recreate base class items (or instance) from a property of the inherited class](https://stackoverflow.com/questions/7788115/class-inheritance-recreate-base-class-items-or-instance-from-a-property-of-th)
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Tuple.cs
