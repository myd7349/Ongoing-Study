namespace ActorLite
{
    using System.Collections.Generic;

    public abstract class Actor<T> : IActor
    {
        protected Actor()
        {
            context_ = new ActorContext(this);
            messages_ = new Queue<T>();
        }


        void IActor.Execute()
        {
            T message;

            lock(messages_)
            {
                message = messages_.Dequeue();
            }

            Receive(message);
        }

        bool IActor.Exited
        {
            get
            {
                return exited_;
            }
        }

        int IActor.MessageCount
        {
            get
            {
                return messages_.Count;
            }
        }

        ActorContext IActor.Context
        {
            get
            {
                return context_;
            }
        }

        protected abstract void Receive(T message);

        protected void Exit()
        {
            exited_ = true;
        }

        public void Post(T message)
        {
            if (exited_)
                return;

            lock (messages_)
            {
                messages_.Enqueue(message);
            }

            Dispatcher.Instance.ReadyToExecute(this);
        }

        private bool exited_ = false;
        private ActorContext context_;
        private Queue<T> messages_;
    }
}
