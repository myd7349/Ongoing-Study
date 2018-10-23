namespace ActorLite
{
    using System.Threading;

    internal class Dispatcher
    {
        public static Dispatcher Instance = new Dispatcher();

        public void ReadyToExecute(IActor actor)
        {
            if (actor.Exited)
                return;

            int status = Interlocked.CompareExchange(
                ref actor.Context.Status,
                ActorContext.EXECUTING,
                ActorContext.WAITING);

            if (status == ActorContext.WAITING)
                ThreadPool.QueueUserWorkItem(Execute, actor);
        }

        private void Execute(object o)
        {
            IActor actor = o as IActor;
            actor.Execute();

            if (actor.Exited)
            {
                Thread.VolatileWrite(
                    ref actor.Context.Status,
                    ActorContext.EXITED);
            }
            else
            {
                Thread.VolatileWrite(
                    ref actor.Context.Status,
                    ActorContext.WAITING);

                if (actor.MessageCount > 0)
                    ReadyToExecute(actor);
            }
        }
    }
}
