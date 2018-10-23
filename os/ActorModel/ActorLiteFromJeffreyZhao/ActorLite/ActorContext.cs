namespace ActorLite
{
    internal class ActorContext
    {
        public ActorContext(IActor actor)
        {
            this.Actor = actor;
        }

        public IActor Actor
        {
            get;
            private set;
        }

        public const int WAITING = 0;
        public const int EXECUTING = 1;
        public const int EXITED = 2;

        public int Status = WAITING;
    }
}
