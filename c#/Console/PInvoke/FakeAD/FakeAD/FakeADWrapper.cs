//#define ARCH_32

using System;

namespace FakeAD
{
    public class FakeADWrapper : IDisposable
    {
        public FakeADWrapper(
            uint bytesPerSecond,
            uint timeSliceInMilliseconds,
            uint timeoutSliceCount,
            ushort port,
#if ARCH_32
            FakeADCallback32 callback,
#else
            FakeADCallback64 callback,
#endif
            IntPtr context)
        {
            if (Natives.Is64Bit)
            {
                callback_ = callback;

                config64_.BytesPerSecond = bytesPerSecond;
                config64_.TimeSliceInMilliseconds = timeSliceInMilliseconds;
                config64_.TimeoutSliceCount = timeoutSliceCount;
                config64_.Port = port;
                config64_.WSAStartup = 1;
                config64_.Callback = callback_;
                config64_.Context = context;

                handle_ = Natives.Init64(ref config64_);
            }
            else
            {
#if ARCH_32
                callback_ = callback;

                config32_.BytesPerSecond = bytesPerSecond;
                config32_.TimeSliceInMilliseconds = timeSliceInMilliseconds;
                config32_.TimeoutSliceCount = timeoutSliceCount;
                config32_.Port = port;
                config32_.WSAStartup = 1;
                config32_.Callback = callback_;
                config32_.Context = context;

                handle_ = Natives.Init32(ref config32_);
#endif
            }

            if (handle_ == IntPtr.Zero)
                throw new Exception(ErrorToString(GetLastError()));
        }

        // Use C# finalizer syntax for finalization code.
        // This finalizer will run only if the Dispose method
        // does not get called.
        // It gives your base class the opportunity to finalize.
        // Do not provide finalizer in types derived from this class.
        ~FakeADWrapper()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(disposing: false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
        }

#if ARCH_32
        public uint Read(IntPtr buffer, uint size)
#else
        public ulong Read(IntPtr buffer, ulong size)
#endif
        {
            if (handle_ == IntPtr.Zero)
                throw new InvalidOperationException("fakead not initialized.");

#if ARCH_32
            return Natives.Read32(handle_, buffer, size);
#else
            return Natives.Read64(handle_, buffer, size);
#endif
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
        protected virtual void Dispose(bool disposing)
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
                Natives.Free(ref handle_);
                handle_ = IntPtr.Zero;

                // Note disposing has been done.
                disposed_ = true;
            }
        }

        public static Error GetLastError() => Natives.GetError();

        public static string ErrorToString(Error error) => Natives.ErrorToString(error);

#if ARCH_32
        private readonly FakeADCallback32 callback_;
        private Config32 config32_;
#else
        private readonly FakeADCallback64 callback_;
        private Config64 config64_;
#endif
        private IntPtr handle_;
        private bool disposed_ = false;
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/api/system.idisposable?view=net-6.0
// [Set C# callback on a C++ struct obtained via P/Invoke](https://stackoverflow.com/questions/50818345/set-c-sharp-callback-on-a-c-struct-obtained-via-p-invoke)
