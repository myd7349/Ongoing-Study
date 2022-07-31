using System;

namespace Common
{
    public class DisposableBase : IDisposable
    {
        // Use C# finalizer syntax for finalization code.
        // This finalizer will run only if the Dispose method
        // does not get called.
        // It gives your base class the opportunity to finalize.
        // Do not provide finalizer in types derived from this class.
        ~DisposableBase()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(disposing: false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
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
                    DisposeManaged();
                }

                // Call the appropriate methods to clean up
                // unmanaged resources here.
                // If disposing is false,
                // only the following code is executed.
                DisposeUnmanaged();

                // Note disposing has been done.
                disposed_ = true;
            }
        }

        protected virtual void DisposeManaged()
        {
        }

        protected virtual void DisposeUnmanaged()
        {
        }

        // https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/NetworkStream.cs
        // > ThrowIfDisposed();
        protected void CheckIsDisposed()
        {
            if (disposed_)
                throw new ObjectDisposedException(
                    string.Format("{0} object is disposed.", GetType().Name));
        }

        protected bool disposed_ = false;
    }
}


// References:
// [IDisposable Interface](https://docs.microsoft.com/en-us/dotnet/api/system.idisposable?view=net-6.0)
// https://github.com/Open-NET-Libraries/Open.Disposable
// https://github.com/mono/SkiaSharp/blob/main/binding/Binding/SKObject.cs
// https://github.com/StephenCleary/Disposables
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Threading/CancellationTokenSource.cs
// > ThrowIfDisposed();
// Ongoing-Study/c#/notes/IDisposable.md
// https://github.com/InCerryGit/Dispose.Scope
