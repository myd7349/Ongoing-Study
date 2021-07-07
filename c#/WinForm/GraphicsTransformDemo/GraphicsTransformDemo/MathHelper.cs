namespace GraphicsTransformDemo
{
    using System;

    class MathHelper
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
    }
}


// References:
// [C# Cookbook](https://www.oreilly.com/library/view/c-cookbook/0596003390/ch01s02.html)
