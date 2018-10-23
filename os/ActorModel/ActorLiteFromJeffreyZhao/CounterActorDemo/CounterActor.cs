namespace CounterActorDemo
{
    using System;

    using ActorLite;

    public class CounterActor : Actor<int>
    {
        public const int EXIT = -1;

        public CounterActor(int initial = 0)
        {
            count_ = initial;
        }

        protected override void Receive(int message)
        {
            if (message == EXIT)
            {
                Exit();

                Console.WriteLine("Counter will exit.");
            }
            else
            {
                count_ += message;

                Console.WriteLine("Counter received {0}. Now the new value is: {1}.", message, count_);
            }
        }

        private int count_;
    }
}
