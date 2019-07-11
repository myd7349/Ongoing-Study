namespace CircularBufferTests
{
    using System;

    using Common;
    using Common.Collections.Generic;

    class Program
    {
        static void Main(string[] args)
        {
            var buffer = new CircularBuffer<int>(10);

            Console.WriteLine(buffer);

            buffer.Add(1);
            Console.WriteLine(buffer);

            buffer.Add(2);
            Console.WriteLine(buffer);

            for (int i = 3; i < 10; ++i)
                buffer.Add(i);
            Console.WriteLine(buffer);

            buffer.Add(10);
            Console.WriteLine(buffer);

            buffer.Remove();
            Console.WriteLine(buffer);

            buffer.Add(11);
            Console.WriteLine(buffer);

            var removed = new int[3];
            buffer.RemoveMany(removed, 0, removed.Length);
            Console.WriteLine(removed);
            Console.WriteLine(buffer);

            buffer.AddMany(removed, 0, removed.Length - 1);
            Console.WriteLine(buffer);

            foreach (var elem in buffer)
                Console.WriteLine(elem);

            Util.Pause();
        }
    }
}
