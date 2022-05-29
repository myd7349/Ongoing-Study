// 2017-04-06T12:29:12+08:00
// What?
// A C# analog to C++11's std::minmax_element.
// Why?
// I want to get the maximum and minimum elements within one looping.
// How?
// First, make a copy of `GitHub/Microsoft/corefx/src/System.Linq/src/System/Linq/Min.cs`.
// Second, rename all `Min`s to `MinMax`s.
// At last, enjoy it!
using System;
using System.Collections.Generic;
using System.Linq;

namespace Common.Linq
{
    public static partial class EnumerableExtension
    {
        public static Pair<int, int> MinMax(this IEnumerable<int> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            Pair<int, int> result;
            using (IEnumerator<int> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                result.First = result.Second = e.Current;
                while (e.MoveNext())
                {
                    int x = e.Current;
                    if (x < result.First)
                    {
                        result.First = x;
                    }

                    if (x > result.Second)
                    {
                        result.Second = x;
                    }
                }
            }

            return result;
        }

        public static Pair<int?, int?> MinMax(this IEnumerable<int?> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            var result = new Pair<int?, int?>();
            int? value = null;
            using (var e = source.GetEnumerator())
            {
                // Start off knowing that we've a non-null value (or exit here, knowing we don't)
                // so we don't have to keep testing for nullity.
                do
                {
                    if (!e.MoveNext())
                    {
                        result.First = result.Second = value;
                        return result;
                    }

                    value = e.Current;
                }
                while (!value.HasValue);

                int? valueMin = value;
                int? valueMax = value;

                // Keep hold of the wrapped value, and do comparisons on that, rather than
                // using the lifted operation each time.
                int valueValMin;
                int valueValMax;
                valueValMin = valueValMax = value.GetValueOrDefault();

                while (e.MoveNext())
                {
                    int? cur = e.Current;

                    if (cur.HasValue)
                    {
                        int x = cur.GetValueOrDefault();

                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }

                result.First = valueMin;
                result.Second = valueMax;
            }

            return result;
        }

        public static Pair<long, long> MinMax(this IEnumerable<long> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            Pair<long, long> result;
            using (IEnumerator<long> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                result.First = result.Second = e.Current;
                while (e.MoveNext())
                {
                    long x = e.Current;
                    if (x < result.First)
                    {
                        result.First = x;
                    }

                    if (x > result.Second)
                    {
                        result.Second = x;
                    }
                }
            }

            return result;
        }

        public static Pair<long?, long?> MinMax(this IEnumerable<long?> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            var result = new Pair<long?, long?>();
            long? value = null;
            using (var e = source.GetEnumerator())
            {
                // Start off knowing that we've a non-null value (or exit here, knowing we don't)
                // so we don't have to keep testing for nullity.
                do
                {
                    if (!e.MoveNext())
                    {
                        result.First = result.Second = value;
                        return result;
                    }

                    value = e.Current;
                }
                while (!value.HasValue);

                long? valueMin = value;
                long? valueMax = value;

                // Keep hold of the wrapped value, and do comparisons on that, rather than
                // using the lifted operation each time.
                long valueValMin;
                long valueValMax;
                valueValMin = valueValMax = value.GetValueOrDefault();

                while (e.MoveNext())
                {
                    long? cur = e.Current;

                    if (cur.HasValue)
                    {
                        long x = cur.GetValueOrDefault();

                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }

                result.First = valueMin;
                result.Second = valueMax;
            }

            return result;
        }

        public static Pair<float, float> MinMax(this IEnumerable<float> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            float valueMin, valueMax;
            using (var e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No elements");
                }

                valueMin = valueMax = e.Current;

                if (float.IsNaN(valueMin))
                {
                    valueMax = source.Max();
                }
                else
                {
                    bool foundMin = false;

                    while (e.MoveNext())
                    {
                        float x = e.Current;

                        if (!foundMin)
                        {
                            if (x < valueMin)
                            {
                                valueMin = x;
                            }
                            else if (x > valueMax)
                            {
                                valueMax = x;
                            }
                            // Normally NaN < anything is false, as is anything < NaN
                            // However, this leads to some irksome outcomes in Min and Max.
                            // If we use those semantics then Min(NaN, 5.0) is NaN, but
                            // Min(5.0, NaN) is 5.0!  To fix this, we impose a total
                            // ordering where NaN is smaller than every value, including
                            // negative infinity.
                            else if (float.IsNaN(x))
                            {
                                valueMin = x;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueMax)
                            {
                                valueMax = x;
                            }
                        }
                    }
                }
            }

            return new Pair<float, float>(valueMin, valueMax);
        }

        public static Pair<float?, float?> MinMax(this IEnumerable<float?> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            float? valueMin = null;
            float? valueMax = null;

            float? value = null;
            using (var e = source.GetEnumerator())
            {
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<float?, float?>(value, value);
                    }

                    value = e.Current;
                }
                while (!value.HasValue);

                float valueValMin;
                float valueValMax;
                valueValMin = valueValMax = value.GetValueOrDefault();

                bool foundMin = false;

                while (e.MoveNext())
                {
                    float? cur = e.Current;
                    if (cur.HasValue)
                    {
                        float x = cur.GetValueOrDefault();

                        if (!foundMin)
                        {
                            if (x < valueValMin)
                            {
                                valueValMin = x;
                                valueMin = cur;
                            }
                            else if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                            else if (float.IsNaN(x))
                            {
                                valueValMin = x;
                                valueMin = cur;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                        }
                    }
                }
            }

            return new Pair<float?, float?>(valueMin, valueMax);
        }

        public static Pair<double, double> MinMax(this IEnumerable<double> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            double valueMin, valueMax;
            using (var e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No elements");
                }

                valueMin = valueMax = e.Current;

                if (double.IsNaN(valueMin))
                {
                    valueMax = source.Max();
                }
                else
                {
                    bool foundMin = false;

                    while (e.MoveNext())
                    {
                        var x = e.Current;

                        if (!foundMin)
                        {
                            if (x < valueMin)
                            {
                                valueMin = x;
                            }
                            else if (x > valueMax)
                            {
                                valueMax = x;
                            }
                            // Normally NaN < anything is false, as is anything < NaN
                            // However, this leads to some irksome outcomes in Min and Max.
                            // If we use those semantics then Min(NaN, 5.0) is NaN, but
                            // Min(5.0, NaN) is 5.0!  To fix this, we impose a total
                            // ordering where NaN is smaller than every value, including
                            // negative infinity.
                            else if (double.IsNaN(x))
                            {
                                valueMin = x;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueMax)
                            {
                                valueMax = x;
                            }
                        }
                    }
                }
            }

            return new Pair<double, double>(valueMin, valueMax);
        }

        public static Pair<double?, double?> MinMax(this IEnumerable<double?> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            double? valueMin = null;
            double? valueMax = null;

            double? value = null;
            using (var e = source.GetEnumerator())
            {
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<double?, double?>(value, value);
                    }

                    value = e.Current;
                }
                while (!value.HasValue);

                double valueValMin;
                double valueValMax;
                valueValMin = valueValMax = value.GetValueOrDefault();

                bool foundMin = false;

                while (e.MoveNext())
                {
                    double? cur = e.Current;
                    if (cur.HasValue)
                    {
                        double x = cur.GetValueOrDefault();

                        if (!foundMin)
                        {
                            if (x < valueValMin)
                            {
                                valueValMin = x;
                                valueMin = cur;
                            }
                            else if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                            else if (double.IsNaN(x))
                            {
                                valueValMin = x;
                                valueMin = cur;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                        }
                    }
                }
            }

            return new Pair<double?, double?>(valueMin, valueMax);
        }

        public static Pair<decimal, decimal> MinMax(this IEnumerable<decimal> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            Pair<decimal, decimal> result;
            using (var e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                result.First = result.Second = e.Current;
                while (e.MoveNext())
                {
                    var x = e.Current;
                    if (x < result.First)
                    {
                        result.First = x;
                    }

                    if (x > result.Second)
                    {
                        result.Second = x;
                    }
                }
            }

            return result;
        }

        public static Pair<decimal?, decimal?> MinMax(this IEnumerable<decimal?> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            var result = new Pair<decimal?, decimal?>();
            decimal? value = null;
            using (var e = source.GetEnumerator())
            {
                // Start off knowing that we've a non-null value (or exit here, knowing we don't)
                // so we don't have to keep testing for nullity.
                do
                {
                    if (!e.MoveNext())
                    {
                        result.First = result.Second = value;
                        return result;
                    }

                    value = e.Current;
                }
                while (!value.HasValue);

                decimal? valueMin = value;
                decimal? valueMax = value;

                // Keep hold of the wrapped value, and do comparisons on that, rather than
                // using the lifted operation each time.
                decimal valueValMin;
                decimal valueValMax;
                valueValMin = valueValMax = value.GetValueOrDefault();

                while (e.MoveNext())
                {
                    decimal? cur = e.Current;

                    if (cur.HasValue)
                    {
                        var x = cur.GetValueOrDefault();

                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }

                result.First = valueMin;
                result.Second = valueMax;
            }

            return result;
        }

        public static Pair<TSource, TSource> MinMax<TSource>(this IEnumerable<TSource> source)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            var valueMin = default(TSource);
            var valueMax = default(TSource);

            Comparer<TSource> comparer = Comparer<TSource>.Default;
            TSource value = default(TSource);

            if (value == null)
            {
                using (var e = source.GetEnumerator())
                {
                    do
                    {
                        if (!e.MoveNext())
                        {
                            return new Pair<TSource, TSource>(value, value);
                        }

                        value = e.Current;
                    }
                    while (value == null);

                    valueMin = valueMax = value;

                    while (e.MoveNext())
                    {
                        TSource x = e.Current;
                        if (x != null)
                        {
                            if (comparer.Compare(x, valueMin) < 0)
                            {
                                valueMin = x;
                            }
                            else if (comparer.Compare(x, valueMax) > 0)
                            {
                                valueMax = x;
                            }
                        }
                    }
                }
            }
            else
            {
                using (var e = source.GetEnumerator())
                {
                    if (!e.MoveNext())
                    {
                        throw new ArgumentException("No elements");
                    }

                    valueMin = valueMax = e.Current;

                    while (e.MoveNext())
                    {
                        TSource x = e.Current;
                        if (comparer.Compare(x, valueMin) < 0)
                        {
                            valueMin = x;
                        }
                        else if (comparer.Compare(x, valueMax) > 0)
                        {
                            valueMax = x;
                        }
                    }
                }
            }

            return new Pair<TSource, TSource>(valueMin, valueMax);
        }

        public static Pair<int, int> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, int> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            int valueMin, valueMax;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                valueMin = valueMax = selector(e.Current);
                while (e.MoveNext())
                {
                    int x = selector(e.Current);
                    if (x < valueMin)
                    {
                        valueMin = x;
                    }
                    else if (x > valueMax)
                    {
                        valueMax = x;
                    }
                }
            }

            return new Pair<int, int>(valueMin, valueMax);
        }

        public static Pair<int?, int?> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, int?> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            int? valueMin = null;
            int? valueMax = null;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                int? value = null;

                // Start off knowing that we've a non-null value (or exit here, knowing we don't)
                // so we don't have to keep testing for nullity.
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<int?, int?>(value, value);
                    }

                    value = selector(e.Current);
                }
                while (!value.HasValue);

                valueMin = valueMax = value;

                // Keep hold of the wrapped value, and do comparisons on that, rather than
                // using the lifted operation each time.
                int valueValMin = value.GetValueOrDefault();
                int valueValMax = value.GetValueOrDefault();
                while (e.MoveNext())
                {
                    int? cur = selector(e.Current);
                    int x = cur.GetValueOrDefault();

                    if (cur.HasValue)
                    {
                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }
            }

            return new Pair<int?, int?>(valueMin, valueMax);
        }

        public static Pair<long, long> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, long> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            long valueMin, valueMax;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                valueMin = valueMax = selector(e.Current);
                while (e.MoveNext())
                {
                    var x = selector(e.Current);
                    if (x < valueMin)
                    {
                        valueMin = x;
                    }
                    else if (x > valueMax)
                    {
                        valueMax = x;
                    }
                }
            }

            return new Pair<long, long>(valueMin, valueMax);
        }

        public static Pair<long?, long?> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, long?> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            long? valueMin = null;
            long? valueMax = null;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                long? value = null;

                // Start off knowing that we've a non-null value (or exit here, knowing we don't)
                // so we don't have to keep testing for nullity.
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<long?, long?>(value, value);
                    }

                    value = selector(e.Current);
                }
                while (!value.HasValue);

                valueMin = valueMax = value;

                // Keep hold of the wrapped value, and do comparisons on that, rather than
                // using the lifted operation each time.
                long valueValMin = value.GetValueOrDefault();
                long valueValMax = value.GetValueOrDefault();
                while (e.MoveNext())
                {
                    long? cur = selector(e.Current);
                    long x = cur.GetValueOrDefault();

                    if (cur.HasValue)
                    {
                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }
            }

            return new Pair<long?, long?>(valueMin, valueMax);
        }

        public static Pair<float, float> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, float> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            float valueMin, valueMax;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                valueMin = valueMax = selector(e.Current);
                bool foundMin = false;

                while (e.MoveNext())
                {
                    float x = selector(e.Current);

                    if (!foundMin)
                    {
                        if (x < valueMin)
                        {
                            valueMin = x;
                        }
                        else if (x > valueMax)
                        {
                            valueMax = x;
                        }
                        else if (float.IsNaN(x))
                        {
                            valueMin = x;
                            foundMin = true;
                        }
                    }
                    else
                    {
                        if (x > valueMax)
                        {
                            valueMax = x;
                        }
                    }
                }
            }

            return new Pair<float, float>(valueMin, valueMax);
        }

        public static Pair<float?, float?> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, float?> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            float? valueMin = null;
            float? valueMax = null;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                float? value = null;
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<float?, float?>(value, value);
                    }

                    value = selector(e.Current);
                }
                while (!value.HasValue);

                valueMin = valueMax = value;

                float valueValMin = value.GetValueOrDefault();
                float valueValMax = value.GetValueOrDefault();

                bool foundMin = false;

                while (e.MoveNext())
                {
                    float? cur = selector(e.Current);
                    if (cur.HasValue)
                    {
                        float x = cur.GetValueOrDefault();

                        if (!foundMin)
                        {
                            if (x < valueValMin)
                            {
                                valueValMin = x;
                                valueMin = cur;
                            }
                            else if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                            else if (float.IsNaN(x))
                            {
                                valueValMin = x;
                                valueMin = cur;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                        }
                    }
                }
            }

            return new Pair<float?, float?>(valueMin, valueMax);
        }

        public static Pair<double, double> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, double> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            double valueMin, valueMax;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                valueMin = valueMax = selector(e.Current);
                bool foundMin = false;

                while (e.MoveNext())
                {
                    var x = selector(e.Current);

                    if (!foundMin)
                    {
                        if (x < valueMin)
                        {
                            valueMin = x;
                        }
                        else if (x > valueMax)
                        {
                            valueMax = x;
                        }
                        else if (double.IsNaN(x))
                        {
                            valueMin = x;
                            foundMin = true;
                        }
                    }
                    else
                    {
                        if (x > valueMax)
                        {
                            valueMax = x;
                        }
                    }
                }
            }

            return new Pair<double, double>(valueMin, valueMax);
        }

        public static Pair<double?, double?> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, double?> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            double? valueMin = null;
            double? valueMax = null;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                double? value = null;
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<double?, double?>(value, value);
                    }

                    value = selector(e.Current);
                }
                while (!value.HasValue);

                valueMin = valueMax = value;

                var valueValMin = value.GetValueOrDefault();
                var valueValMax = value.GetValueOrDefault();

                bool foundMin = false;

                while (e.MoveNext())
                {
                    double? cur = selector(e.Current);
                    if (cur.HasValue)
                    {
                        var x = cur.GetValueOrDefault();

                        if (!foundMin)
                        {
                            if (x < valueValMin)
                            {
                                valueValMin = x;
                                valueMin = cur;
                            }
                            else if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                            else if (double.IsNaN(x))
                            {
                                valueValMin = x;
                                valueMin = cur;
                                foundMin = true;
                            }
                        }
                        else
                        {
                            if (x > valueValMax)
                            {
                                valueValMax = x;
                                valueMax = cur;
                            }
                        }
                    }
                }
            }

            return new Pair<double?, double?>(valueMin, valueMax);
        }

        public static Pair<decimal, decimal> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, decimal> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            decimal valueMin, valueMax;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                if (!e.MoveNext())
                {
                    throw new ArgumentException("No Elements");
                }

                valueMin = valueMax = selector(e.Current);
                while (e.MoveNext())
                {
                    var x = selector(e.Current);
                    if (x < valueMin)
                    {
                        valueMin = x;
                    }
                    else if (x > valueMax)
                    {
                        valueMax = x;
                    }
                }
            }

            return new Pair<decimal, decimal>(valueMin, valueMax);
        }

        public static Pair<decimal?, decimal?> MinMax<TSource>(this IEnumerable<TSource> source, Func<TSource, decimal?> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            decimal? valueMin = null;
            decimal? valueMax = null;
            using (IEnumerator<TSource> e = source.GetEnumerator())
            {
                decimal? value = null;
                do
                {
                    if (!e.MoveNext())
                    {
                        return new Pair<decimal?, decimal?>(value, value);
                    }

                    value = selector(e.Current);
                }
                while (!value.HasValue);

                valueMin = valueMax = value;

                decimal valueValMin = value.GetValueOrDefault();
                decimal valueValMax = value.GetValueOrDefault();

                while (e.MoveNext())
                {
                    decimal? cur = selector(e.Current);
                    decimal x = cur.GetValueOrDefault();
                    if (cur.HasValue)
                    {
                        if (x < valueValMin)
                        {
                            valueValMin = x;
                            valueMin = cur;
                        }
                        else if (x > valueValMax)
                        {
                            valueValMax = x;
                            valueMax = cur;
                        }
                    }
                }
            }

            return new Pair<decimal?, decimal?>(valueMin, valueMax);
        }

        public static Pair<TResult, TResult> MinMax<TSource, TResult>(this IEnumerable<TSource> source, Func<TSource, TResult> selector)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (selector == null)
            {
                throw new ArgumentNullException(nameof(selector));
            }

            TResult valueMin = default(TResult);
            TResult valueMax = default(TResult);

            Comparer<TResult> comparer = Comparer<TResult>.Default;
            TResult value = default(TResult);
            if (value == null)
            {
                using (IEnumerator<TSource> e = source.GetEnumerator())
                {
                    do
                    {
                        if (!e.MoveNext())
                        {
                            return new Pair<TResult, TResult>(value, value);
                        }

                        value = selector(e.Current);
                    }
                    while (value == null);

                    valueMin = valueMax = value;

                    while (e.MoveNext())
                    {
                        TResult x = selector(e.Current);
                        if (x != null)
                        {
                            if (comparer.Compare(x, valueMin) < 0)
                            {
                                valueMin = x;
                            }
                            else if (comparer.Compare(x, valueMax) > 0)
                            {
                                valueMax = x;
                            }
                        }
                    }
                }
            }
            else
            {
                using (IEnumerator<TSource> e = source.GetEnumerator())
                {
                    if (!e.MoveNext())
                    {
                        throw new ArgumentException("No Elements");
                    }

                    valueMin = valueMax = selector(e.Current);
                    while (e.MoveNext())
                    {
                        TResult x = selector(e.Current);
                        if (comparer.Compare(x, valueMin) < 0)
                        {
                            valueMin = x;
                        }
                        else if (comparer.Compare(x, valueMax) > 0)
                        {
                            valueMax = x;
                        }
                    }
                }
            }

            return new Pair<TResult, TResult>(valueMin, valueMax);
        }
    }
}


// References:
// [Get Max and Min in a single LINQ query](https://stackoverflow.com/questions/22240167/get-max-and-min-in-a-single-linq-query)
