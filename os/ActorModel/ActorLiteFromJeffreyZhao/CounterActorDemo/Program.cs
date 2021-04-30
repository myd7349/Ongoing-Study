namespace CounterActorDemo
{
    using System;

    class Program
    {
        static void Main(string[] args)
        {
            var counter = new CounterActor();
            for (int i = 1; i <= 10; ++i)
                counter.Post(i);

            counter.Post(CounterActor.EXIT);

            Console.WriteLine("Press any key to quit!");
            Console.ReadKey();
        }
    }
}

// References:
// https://github.com/akkadotnet/akka.net/issues/4659
