namespace Native.Interop
{
    using System;
    using System.Runtime.InteropServices;
    using System.Security;

    /// <summary>
    /// This class declares P/Invoke methods to call native POSIX APIs.
    /// </summary>
    [SuppressUnmanagedCodeSecurity]
    internal static class UnsafeNativeMethodsPosix
    {
        /// <summary>
        /// For use with dlopen(), bind function calls lazily.
        /// </summary>
        internal const int RTLD_LAZY = 1;

        /// <summary>
        /// For use with dlopen(), bind function calls immediately.
        /// </summary>
        internal const int RTLD_NOW = 2;

        /// <summary>
        /// For use with dlopen(), make symbols globally available.
        /// </summary>
        internal const int RTLD_GLOBAL = 256;

        /// <summary>
        /// For use with dlopen(), opposite of RTLD_GLOBAL, and the default.
        /// </summary>
        internal const int RTLD_LOCAL = 0;

        /// <summary>
        /// For use with dlopen(), the defaults used by this class.
        /// </summary>
        internal const int RTLD_DEFAULT = 258;

        /// <summary>
        /// This is the P/Invoke method that wraps the native Unix dlopen
        /// function.  See the POSIX documentation for full details on what it
        /// does.
        /// </summary>
        /// <param name="fileName">
        /// The name of the executable library.
        /// </param>
        /// <param name="mode">
        /// This must be a combination of the individual bit flags RTLD_LAZY,
        /// RTLD_NOW, RTLD_GLOBAL, and/or RTLD_LOCAL.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        [DllImport("__Internal", BestFitMapping = false, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, SetLastError = true, ThrowOnUnmappableChar = true)]
        internal static extern IntPtr dlopen(string fileName, int mode);
    }
}
