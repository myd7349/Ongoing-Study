namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public sealed class UnmanagedBuffer : IDisposable
    {
        public static implicit operator IntPtr(UnmanagedBuffer buffer)
        {
            return buffer.handle_;
        }

        public UnmanagedBuffer(int bytes)
        {
            handle_ = Marshal.AllocHGlobal(bytes);
        }

        // NOTE: Leave out the finalizer altogether if this class doesn't
        // own unmanaged resources, but leave the other methods
        // exactly as they are.
        ~UnmanagedBuffer()
        {
            // Finalizer calls Dispose(false)
            Dispose(false);
        }

        public void CopyFrom(byte[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyFrom(int[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyFrom(double[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyTo(byte[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
        }

        public void CopyTo(int[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
        }

        public void CopyTo(double[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
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
            Marshal.FreeHGlobal(handle_);

            disposed_ = true;
        }

        private IntPtr handle_;
        private bool disposed_ = false;
    }
}

// References:
// [How to get IntPtr from byte[] in C#](https://stackoverflow.com/questions/537573/how-to-get-intptr-from-byte-in-c-sharp)
// [CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)
