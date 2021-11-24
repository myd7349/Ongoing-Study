namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public sealed class PinnedObject : IDisposable
    {
        public static implicit operator IntPtr(PinnedObject obj)
        {
            return obj.handle_.AddrOfPinnedObject();
        }

        public PinnedObject(object obj)
        {
            handle_ = GCHandle.Alloc(obj, GCHandleType.Pinned);
        }

        // NOTE: Leave out the finalizer altogether if this class doesn't
        // own unmanaged resources, but leave the other methods
        // exactly as they are.
        ~PinnedObject()
        {
            // Finalizer calls Dispose(false)
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                // Free managed resources
                // 1.
            }

            // Free native resources if there are any.
            // 2.
            handle_.Free(); // TODO: Should I put this line at 1 or 2?

            disposed_ = true;
        }

        private GCHandle handle_;
        private bool disposed_ = false;
    }
}

// References:
// [How to get IntPtr from byte[] in C#](https://stackoverflow.com/questions/537573/how-to-get-intptr-from-byte-in-c-sharp)
// [CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)
// https://referencesource.microsoft.com/#system/compmod/microsoft/win32/safehandles/SafeLibraryHandle.cs
// https://github.com/dahall/Vanara/blob/8ca58cc2c8d5ca87c19a434f06b6b2f6810aa313/Core/InteropServices/SafeHGlobalHandle.cs#L117
// public static SafeHGlobalHandle CreateFromStructure<T>(in T value = default) => new SafeHGlobalHandle(InteropExtensions.MarshalToPtr(value, mm.AllocMem, out int s), s);
