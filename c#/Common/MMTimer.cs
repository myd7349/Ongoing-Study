namespace Common
{
    using System;
    using System.Diagnostics;
    using System.Runtime.InteropServices;
    using System.Threading;

    public class MMTimer : IDisposable
    {
        public MMTimer(SynchronizationContext synchronizationContext = null)
        {
            callback_ = new MMTimerCallback(TimerCallback);

            if (synchronizationContext != null)
                synchronizationContext_ = synchronizationContext;
            else
                synchronizationContext_ = SynchronizationContext.Current ?? MMTimerStatics.DefaultContext;

            Debug.Assert(synchronizationContext_ != null);

            invokeHandlers_ = new SendOrPostCallback(InvokeHandlers);
        }

        public MMTimer(Action<object> action, object state = null, SynchronizationContext synchronizationContext = null)
            : this(synchronizationContext)
        {
            handler_ = action;
            state_ = state;
        }

        ~MMTimer()
        {
            Dispose(false);
        }

        public int Interval
        {
            get
            {
                return interval_;
            }

            set
            {
                if (disposed_)
                    throw new ObjectDisposedException("MMTimer");

                if (value < 0)
                    throw new ArgumentOutOfRangeException("Interval");

                if (IsRunning)
                    throw new InvalidOperationException("Timer is already running");

                interval_ = value;
                if (Resolution > interval_)
                    Resolution = interval_;
            }
        }

        // Note minimum resolution is 0, meaning highest possible resolution.
        public int Resolution
        {
            get
            {
                return resolution_;
            }
            set
            {
                if (disposed_)
                    throw new ObjectDisposedException("MMTimer");

                if (value < 0)
                    throw new ArgumentOutOfRangeException("Resolution");

                if (IsRunning)
                    throw new InvalidOperationException("Timer is already running");

                resolution_ = value;
            }
        }

        public bool IsPeriodic
        {
            get
            {
                return isPeriodic_;
            }

            set
            {
                if (disposed_)
                    throw new ObjectDisposedException("MMTimer");

                if (IsRunning)
                    throw new InvalidOperationException("Timer is already running");

                isPeriodic_ = value;
            }
        }

        public bool IsRunning
        {
            get
            {
                return timerId_ != 0;
            }
        }

        public void Start()
        {
            // Kill any existing timer
            Stop();

            // Set the timer type flags
            TimerType timerType = TimerType.TIME_CALLBACK_FUNCTION |
                TimerType.TIME_KILL_SYNCHRONOUS |
                (IsPeriodic ? TimerType.TIME_PERIODIC : TimerType.TIME_ONESHOT);

            lock (lock_)
            {
                timerId_ = timeSetEvent((uint)Interval, (uint)Resolution, callback_, UIntPtr.Zero, (uint)timerType);
                if (timerId_ == 0)
                    throw new Exception("timeSetEvent error");

                Debug.WriteLine("MMTimer " + timerId_.ToString() + " started");
            }
        }

        public void Stop()
        {
            lock (lock_)
            {
                if (timerId_ != 0)
                {
                    timeKillEvent(timerId_);
                    Debug.WriteLine("MMTimer " + timerId_.ToString() + " stopped");
                    timerId_ = 0;
                }
            }
        }

        public event EventHandler<object> Tick;

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!disposed_)
            {
                if (disposing)
                {
                    Stop();
                }
            }

            disposed_ = true;
        }

        protected virtual void OnTimer(object state)
        {
            Action<object> handler = handler_;
            var tickEvent = Tick;

            if (handler != null || tickEvent != null)
                synchronizationContext_.Post(InvokeHandlers, state);
        }

        private void TimerCallback(uint uTimerID, uint uMsg, UIntPtr dwUser, UIntPtr dw1, UIntPtr dw2)
        {
            // Callback from the MMTimer API that fires the Timer event. Note we are in a different thread here
            OnTimer(state_);
        }

        private void InvokeHandlers(object state)
        {
            Action<object> handler = handler_;
            var tickEvent = Tick;

            handler?.Invoke(state);
            tickEvent?.Invoke(this, state);
        }

        // Hold the timer callback to prevent garbage collection.
        private readonly MMTimerCallback callback_;
        private uint timerId_ = 0;
        private int interval_;
        private int resolution_ = 0;
        private bool isPeriodic_ = true;
        private bool disposed_ = false;
        private Action<object> handler_;
        private object state_;
        private SynchronizationContext synchronizationContext_;
        private readonly SendOrPostCallback invokeHandlers_;
        private readonly object lock_ = new object();

        private delegate void MMTimerCallback(uint uTimerID, uint uMsg, UIntPtr dwUser, UIntPtr dw1, UIntPtr dw2);

        [Flags]
        private enum TimerType : uint
        {
            TIME_ONESHOT = 0, // Event occurs once, after uDelay milliseconds.
            TIME_PERIODIC = 1,
            TIME_CALLBACK_FUNCTION = 0x0000,  // callback is function
            //TIME_CALLBACK_EVENT_SET = 0x0010, // callback is event - use SetEvent
            //TIME_CALLBACK_EVENT_PULSE = 0x0020, // callback is event - use PulseEvent
            TIME_KILL_SYNCHRONOUS = 0x0100,
        }

        [Obsolete("This function is obsolete. New applications should use CreateTimerQueueTimer to create a timer-queue timer.")]
        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        private static extern uint timeSetEvent(uint uDelay, uint uResolution, MMTimerCallback lpTimeProc, UIntPtr dwUser, uint eventType);

        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        private static extern uint timeKillEvent(uint uTimerID);

        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        private static extern uint timeGetTime();

        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        private static extern uint timeBeginPeriod(uint uPeriod);

        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        private static extern uint timeEndPeriod(uint uPeriod);
    }

    internal static class MMTimerStatics
    {
        internal static readonly SynchronizationContext DefaultContext = new SynchronizationContext();
    }
}

// References:
// https://stackoverflow.com/questions/9228313/most-accurate-timer-in-net
// http://pinvoke.net/default.aspx/winmm/timeSetEvent.html
// https://stackoverflow.com/questions/251391/why-is-lockthis-bad
// https://stackoverflow.com/questions/19577296/thread-safety-of-system-timers-timer-vs-system-threading-timer
// https://stackoverflow.com/questions/1759352/how-to-mark-a-method-as-obsolete-or-deprecated
// [High resolution timer in C#](https://stackoverflow.com/questions/24839105/high-resolution-timer-in-c-sharp)
// [What is the meaning of TIME_KILL_SYNCHRONOUS?](https://stackoverflow.com/questions/23403566/what-is-the-meaning-of-time-kill-synchronous)
// [Multimedia Timer limitations or why it stops firing randomly](https://stackoverflow.com/questions/33091639/multimedia-timer-limitations-or-why-it-stops-firing-randomly)
// [How can I use CreateTimerQueueTimer to create a high resolution timer in C#?](https://stackoverflow.com/questions/1015769/how-can-i-use-createtimerqueuetimer-to-create-a-high-resolution-timer-in-c)
// [High precision timers in C#](https://social.msdn.microsoft.com/Forums/en-US/822aed2d-dca0-4a8e-8130-20fab69557d2/high-precision-timers-in-c?forum=csharpgeneral)
// https://github.com/OneDAS-Group/OneDAS-Core/blob/master/src/OneDas.Core/Engine/RtTimer.cs
