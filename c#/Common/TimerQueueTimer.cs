using System;
using System.Runtime.InteropServices;

namespace Common
{
    public enum WTFlags
    {
        WT_EXECUTEDEFAULT = 0x00000000,
        WT_EXECUTEINIOTHREAD = 0x00000001,
        WT_EXECUTEINWAITTHREAD = 0x00000004,
        WT_EXECUTEONLYONCE = 0x00000008,
        WT_EXECUTELONGFUNCTION = 0x00000010,
        WT_EXECUTEINTIMERTHREAD = 0x00000020,
        WT_EXECUTEINPERSISTENTTHREAD = 0x00000080,
        WT_TRANSFER_IMPERSONATION = 0x00000100,
        WT_EXECUTEINLONGTHREAD = 0x00000010,
        WT_EXECUTEDELETEWAIT = 0x00000008,
    }

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void WaitOrTimerDelegate(IntPtr lpParameter, [MarshalAs(UnmanagedType.U1)] bool timerOrWaitFired);

    public class TimerQueueTimerException : Exception
    {
        public TimerQueueTimerException(string message)
            : base(message)
        {
        }

        public TimerQueueTimerException(string message, Exception innerException)
            : base(message, innerException)
        {
        }
    }

    public class TimerQueueTimer : IDisposable
    {
        // Use C# finalizer syntax for finalization code.
        // This finalizer will run only if the Dispose method
        // does not get called.
        // It gives your base class the opportunity to finalize.
        // Do not provide finalizer in types derived from this class.
        ~TimerQueueTimer()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(disposing: false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
        }

        public void Create(uint dueTime, uint period, WaitOrTimerDelegate callback, WTFlags flags = WTFlags.WT_EXECUTEDEFAULT)
        {
            var ok = CreateTimerQueueTimer(
                out timerHandle_,
                IntPtr.Zero,
                callback, IntPtr.Zero,
                dueTime, period,
                (uint)flags);

            if (!ok)
                throw new TimerQueueTimerException("Failed to create TimerQueueTimer.");
        }

        public void Delete()
        {
            if (timerHandle_ != IntPtr.Zero)
            {
                if (DeleteTimerQueueTimer(IntPtr.Zero, timerHandle_, IntPtr.Zero))
                    timerHandle_ = IntPtr.Zero;
            }
        }

        // Implement IDisposable.
        // Do not make this method virtual.
        // A derived class should not be able to override this method.
        public void Dispose()
        {
            Dispose(true);
            // This object will be cleaned up by the Dispose method.
            // Therefore, you should call GC.SuppressFinalize to
            // take this object off the finalization queue
            // and prevent finalization code for this object
            // from executing a second time.
            GC.SuppressFinalize(this);
        }

        // Dispose(bool disposing) executes in two distinct scenarios.
        // If disposing equals true, the method has been called directly
        // or indirectly by a user's code. Managed and unmanaged resources
        // can be disposed.
        // If disposing equals false, the method has been called by the
        // runtime from inside the finalizer and you should not reference
        // other objects. Only unmanaged resources can be disposed.
        private void Dispose(bool disposing)
        {
            // Check to see if Dispose has already been called.
            if (!disposed_)
            {
                // If disposing equals true, dispose all managed
                // and unmanaged resources.
                if (disposing)
                {
                    // Dispose managed resources.
                }

                // Call the appropriate methods to clean up
                // unmanaged resources here.
                // If disposing is false,
                // only the following code is executed.
                Delete();

                // Note disposing has been done.
                disposed_ = true;
            }
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool CreateTimerQueueTimer(
            out IntPtr phNewTimer,
            [In, Optional] IntPtr TimerQueue,
            WaitOrTimerDelegate Callback,
            [In, Optional] IntPtr Parameter,
            uint DueTime,
            [Optional] uint Period,
            [Optional] uint Flags);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool DeleteTimerQueueTimer(
            [In] IntPtr timerQueue,
            [In] IntPtr timer,
            [In] IntPtr completionEvent);

        private IntPtr timerHandle_;
        private bool disposed_ = false;
    }
}


// References:
// [How can I use CreateTimerQueueTimer to create a high resolution timer in C#?](https://stackoverflow.com/questions/1015769/how-can-i-use-createtimerqueuetimer-to-create-a-high-resolution-timer-in-c)
// [High precision timers in C#](https://social.msdn.microsoft.com/Forums/en-US/822aed2d-dca0-4a8e-8130-20fab69557d2/high-precision-timers-in-c?forum=csharpgeneral)
// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-createtimerqueuetimer
// https://www.pinvoke.net/default.aspx/kernel32/CreateTimerQueueTimer.html
// https://github.com/dahall/Vanara/blob/master/PInvoke/Kernel32/ThreadPoolLegacyApiSet.cs
// https://docs.microsoft.com/en-us/dotnet/api/system.idisposable?view=net-6.0
// [Set C# callback on a C++ struct obtained via P/Invoke](https://stackoverflow.com/questions/50818345/set-c-sharp-callback-on-a-c-struct-obtained-via-p-invoke)
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Threading/Timer.cs
// > internal sealed class TimerQueueTimer : IThreadPoolWorkItem
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Threading/CancellationTokenSource.cs
// > private volatile TimerQueueTimer? _timer;

