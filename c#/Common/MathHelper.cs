namespace Common
{
    using System;

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
    }
}


// References:
// [C# Cookbook](https://www.oreilly.com/library/view/c-cookbook/0596003390/ch01s02.html)
// [C# find the greatest common divisor](https://stackoverflow.com/questions/18541832/c-sharp-find-the-greatest-common-divisor)
