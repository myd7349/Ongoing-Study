namespace FilterAPITest
{
    using System;

    using FilterManaged;

    class Program
    {
        static void Main(string[] args)
        {
            {
                double[] data = { 0.0, 0.0, 0.0, 0.0, 0.0 };

                var context = Filter.Initialize(FilterType.FILTER_100HZ);

                foreach (var v in data)
                    Console.WriteLine(Filter.Run(context, v));

                Filter.Free(ref context);
            }

            {
                double[] data = { 0.0, 0.0, 0.0, 0.0, 0.0 };

                var context = Filter.Initialize(FilterType.FILTER_100HZ);
                Filter.Run(context, data, data);

                foreach (var v in data)
                    Console.WriteLine(v);

                Filter.Free(ref context);
            }
        }
    }
}


// References:
// [BadImageFormatException C#](https://stackoverflow.com/questions/15917204/badimageformatexception-c-sharp)
// [Could not load file or assembly … An attempt was made to load a program with an incorrect format (System.BadImageFormatException)](https://stackoverflow.com/questions/11370344/could-not-load-file-or-assembly-an-attempt-was-made-to-load-a-program-with-a)
