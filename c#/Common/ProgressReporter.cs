namespace Common
{
    using System;
    using System.Diagnostics;
    using System.Threading;

    // EventHandler<TEventArgs> in .NET 4.0 requires that `TEventArgs` is
    // derived from `EventArgs`, which is unacceptable here. 
    public delegate void TEventHandler<TEventArgs>(object sender, TEventArgs e);
    
    public class ProgressReporter<T> : IProgressReporter<T>
    {
        private readonly SynchronizationContext _synchronizationContext;

        private readonly Action<T> _handler;

        private readonly SendOrPostCallback _invokeHandlers;

        public ProgressReporter(SynchronizationContext synchronizationContext = null)
        {
            if (synchronizationContext != null)
                _synchronizationContext = synchronizationContext;
            else
                _synchronizationContext = SynchronizationContext.Current ?? ProgressReporterStatics.DefaultContext;
            Debug.Assert(_synchronizationContext != null);
            _invokeHandlers = new SendOrPostCallback(InvokeHandlers);
        }

        public ProgressReporter(Action<T> handler, SynchronizationContext synchronizationContext = null)
            : this(synchronizationContext)
        {
            if (handler == null)
                throw new ArgumentNullException("handler");

            _handler = handler;
        }

        public event TEventHandler<T> ProgressChanged;

        protected virtual void OnReport(T value)
        {
            Action<T> handler = _handler;
            TEventHandler<T> changedEvent = ProgressChanged;

            if (handler != null || changedEvent != null)
                _synchronizationContext.Post(_invokeHandlers, value);
        }

        void IProgressReporter<T>.Report(T value)
        {
            OnReport(value);
        }

        private void InvokeHandlers(object state)
        {
            T value = (T)state;

            Action<T> handler = _handler;
            TEventHandler<T> changedEvent = ProgressChanged;

            if (handler != null)
                handler.Invoke(value);

            if (changedEvent != null)
                changedEvent.Invoke(this, value);
        }
    }

    internal static class ProgressReporterStatics
    {
        internal static readonly SynchronizationContext DefaultContext = new SynchronizationContext();
    }
}

// References:
// https://stackoverflow.com/questions/38719345/iprogresst-in-net-4-0
// https://github.com/dotnet/runtime/blob/master/src/libraries/System.Private.CoreLib/src/System/IProgress.cs
// [The Progress Reporting Pattern in C# 5 async, How to use it and how it works. By Nicholas Butler](http://simplygenius.net/Article/AncillaryAsyncProgress)
