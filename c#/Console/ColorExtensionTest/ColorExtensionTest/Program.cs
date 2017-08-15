namespace ColorExtensionTest
{
    using System;
    using System.Drawing;

    using Common;
    using Common.Auxiliary.Drawing;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Color.Red.ToString(ColorFormat.Auto));

            var skyBlue = Color.FromArgb(166, 202, 240);

            Console.WriteLine(skyBlue.ToString(ColorFormat.Auto));
            Console.WriteLine(skyBlue.ToRGBA());
            Console.WriteLine(skyBlue.ToARGB(true, true));
            Console.WriteLine(skyBlue.ToCOLORREF(true));

            Util.Pause();
        }
    }
}
