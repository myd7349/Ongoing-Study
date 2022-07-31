using System;
using System.Diagnostics;
using System.Threading;
using System.Windows.Threading;

namespace AsyncThread
{
    public sealed class WPFContext : IContext
    {
        public WPFContext() : this(Dispatcher.CurrentDispatcher)
        {
        }

        public WPFContext(Dispatcher dispatcher)
        {
            Debug.Assert(dispatcher != null);

            _dispatcher = dispatcher;
        }

        public bool IsSynchronized
        {
            get
            {
                return _dispatcher.Thread == Thread.CurrentThread;
            }
        }

        public void Invoke(Action action)
        {
            Debug.Assert(action != null);

            _dispatcher.Invoke(action);
        }

        public void Invoke(Action callback, DispatcherPriority priority)
        {
            Debug.Assert(callback != null);

            _dispatcher.Invoke(callback, priority);
        }

        public void Invoke(Action callback, DispatcherPriority priority, CancellationToken cancellationToken)
        {
            Debug.Assert(callback != null);

            _dispatcher.Invoke(callback, priority, cancellationToken);
        }

        public DispatcherOperation InvokeAsync(Action callback, DispatcherPriority priority, CancellationToken cancellationToken)
        {
            Debug.Assert(callback != null);

            return _dispatcher.InvokeAsync(callback, priority, cancellationToken);
        }

        private readonly Dispatcher _dispatcher;
    }
}


// References:
// [How to pass the UI Dispatcher to the ViewModel](https://stackoverflow.com/questions/2354438/how-to-pass-the-ui-dispatcher-to-the-viewmodel)
// [Dispatcher ViewModel?](https://stackoverflow.com/questions/36459534/dispatcher-viewmodel)
// [Is it wrong to use the Dispatcher within my ViewModel?](https://stackoverflow.com/questions/7473973/is-it-wrong-to-use-the-dispatcher-within-my-viewmodel)
// https://github.com/dnSpy/dnSpy/blob/master/dnSpy/dnSpy/UI/UIDispatcher.cs
