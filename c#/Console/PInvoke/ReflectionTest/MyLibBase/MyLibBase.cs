namespace MyLibBase
{
    using static System.Console;

    public abstract class MyLibBase
    {
        public abstract string Message { get; }

        public abstract string Name { get; }

        public void Say()
        {
            WriteLine("Hi! This is a hello message from {0}: {1}", Name, Message);
        }
    }
}
