namespace ActorLite
{
    internal interface IActor
    {
        void Execute();

        bool Exited { get; }

        int MessageCount { get; }

        ActorContext Context { get; }
    }
}
