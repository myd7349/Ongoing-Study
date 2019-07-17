namespace IsDerivedFrom
{
    using System;
    using static System.Console;

    using static Common.Util;

    interface IFoo { }

    abstract class FooBase : IFoo { }

    interface IBar { }

    abstract class BarBase : IBar { }

    class Foo : FooBase { }

    class Program
    {
        public static bool IsDesdencentOfv0<T>(Type type) where T : class
        {
            if (type == null)
                return false;

            var derived = typeof(T);

            while (derived.BaseType != null)
            {
                if (derived.BaseType == type)
                    return true;

                derived = derived.BaseType;
            }

            return false;
        }

        public static bool IsDesdencentOfv1<T>(Type type) where T : class
        {
            return type.IsAssignableFrom(typeof(T));
        }

        static void DoTest<TDerived, TBase>()
            where TDerived : class
            where TBase : class
        {
            WriteLine("Is {0} derived from {1}? {2}",
                typeof(TDerived).Name,
                typeof(TBase).Name,
                IsDesdencentOfv1<TDerived>(typeof(TBase))
                );
        }

        static void Main(string[] args)
        {
            DoTest<Foo, FooBase>();
            DoTest<Foo, IFoo>();
            DoTest<Foo, BarBase>();
            DoTest<Foo, IBar>();

            Pause();
        }
    }
}
