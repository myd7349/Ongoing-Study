namespace Native.Interop
{
    using System;

    internal static class NativeLibraryHelper
    {
        /// <summary>
        /// This delegate is used to wrap the concept of loading a native
        /// library, based on a file name, and returning the loaded module
        /// handle.
        /// </summary>
        /// <param name="fileName">
        /// The file name of the native library to load.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        private delegate IntPtr LoadLibraryCallback(string fileName);

        /// <summary>
        /// Attempts to load the specified native library file using the Win32
        /// API.
        /// </summary>
        /// <param name="fileName">
        /// The file name of the native library to load.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        private static IntPtr LoadLibraryWin32(string fileName)
        {
            return UnsafeNativeMethodsWin32.LoadLibrary(fileName);
        }

        /// <summary>
        /// Attempts to load the specified native library file using the POSIX
        /// API.
        /// </summary>
        /// <param name="fileName">
        /// The file name of the native library to load.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        private static IntPtr LoadLibraryPosix(string fileName)
        {
            return UnsafeNativeMethodsPosix.dlopen(fileName, 258);
        }

        /// <summary>
        /// Attempts to load the specified native library file.
        /// </summary>
        /// <param name="fileName">
        /// The file name of the native library to load.
        /// </param>
        /// <returns>
        /// The native module handle upon success -OR- IntPtr.Zero on failure.
        /// </returns>
        public static IntPtr LoadLibrary(string fileName)
        {
            LoadLibraryCallback loadLibraryCallback = LoadLibraryWin32;
            if (!HelperMethods.IsWindows())
            {
                loadLibraryCallback = LoadLibraryPosix;
            }

            return loadLibraryCallback(fileName);
        }
    }
}


// References:
// https://github.com/chmorgan/sharppcap/blob/master/SharpPcap/LibPcap/NativeLibraryHelper.cs
// https://github.com/mono/SkiaSharp/blob/main/binding/Binding.Shared/LibraryLoader.cs
// https://github.com/mono/SkiaSharp/blob/main/binding/Binding/SkiaApi.cs
// https://github.com/mono/SkiaSharp/issues/190
