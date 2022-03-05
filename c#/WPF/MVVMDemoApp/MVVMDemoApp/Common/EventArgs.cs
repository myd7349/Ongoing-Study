namespace MVVMDemoApp.Common
{
    using System;

    class EventArgs<T> : EventArgs
    {
        public EventArgs(T item)
        {
            item_ = item;
        }

        public T Item => item_;

        private readonly T item_;
    }
}
