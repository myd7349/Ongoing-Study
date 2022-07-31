using System;
using System.Threading;
using System.Windows.Threading;

namespace AsyncThread
{
    public interface IContext
    {
        bool IsSynchronized { get; }

        void Invoke(Action action);

        void Invoke(Action callback, DispatcherPriority priority);
        
        void Invoke(Action callback, DispatcherPriority priority, CancellationToken cancellationToken);

        DispatcherOperation InvokeAsync(Action callback, DispatcherPriority priority, CancellationToken cancellationToken);
    }
}
