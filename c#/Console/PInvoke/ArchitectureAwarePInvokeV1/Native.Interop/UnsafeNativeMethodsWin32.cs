namespace Native.Interop
{
    using System;
    using System.Runtime.InteropServices;
    using System.Security;

    [SuppressUnmanagedCodeSecurity]
    internal static class UnsafeNativeMethodsWin32
    {
        /// <summary>
        /// This is the P/Invoke method that wraps the native Win32 LoadLibrary
        /// function.  See the MSDN documentation for full details on what it
        /// does.
        /// </summary>
        /// <param name="fileName">
        /// The name of the executable library.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        [DllImport("kernel32", BestFitMapping = false, CharSet = CharSet.Auto, SetLastError = true, ThrowOnUnmappableChar = true)]
        internal static extern IntPtr LoadLibrary(string fileName);
    }
}
