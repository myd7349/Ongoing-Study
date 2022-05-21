namespace Common
{
    using System;
    using System.Diagnostics;

    public static class MathHelper
    {
        public static double ConvertDegreesToRadians(double degrees)
        {
            return Math.PI / 180 * degrees;
        }

        public static double Hypotenuse(double a, double b)
        {
            if (a < 0)
                throw new ArgumentException("a");

            if (b < 0)
                throw new ArgumentException("b");

            return Math.Sqrt(Math.Pow(a, 2.0) + Math.Pow(b, 2.0));
        }

        public static uint GCD(uint a, uint b)
        {
            while (a != 0 && b != 0)
            {
                if (a > b)
                    a %= b;
                else
                    b %= a;
            }

            return a | b;
        }

        public static int AlignUp(int a, int b)
        {
            if (a <= 0)
                throw new ArgumentException("a");

            if (b < 1)
                throw new ArgumentException("b");

            return (a + b - 1) / b * b;
        }

        public static float AlignUp(float a, float b)
        {
            if (a <= 0)
                throw new ArgumentException("a");

            if (b <= 0)
                throw new ArgumentException("b");

            if (a < b)
                return b;

            return Convert.ToInt32(a / b + 0.5f) * b;
        }

        public static double AlignUp(double a, double b)
        {
            if (a <= 0)
                throw new ArgumentException("a");

            if (b <= 0)
                throw new ArgumentException("b");

            if (a < b)
                return b;

            return Convert.ToInt32(a / b + 0.5) * b;
        }

        public static int Lerp(int v0, int v1, float t)
        {
            Debug.Assert(v0 < v1);
            Debug.Assert(t >= 0 && t <= 1);

            return (int)(v0 + t * (v1 - v0));
        }
    }
}


// References:
// [C# Cookbook](https://www.oreilly.com/library/view/c-cookbook/0596003390/ch01s02.html)
// [C# find the greatest common divisor](https://stackoverflow.com/questions/18541832/c-sharp-find-the-greatest-common-divisor)
// [C# Lerping from position to position](https://stackoverflow.com/questions/33044848/c-sharp-lerping-from-position-to-position)
