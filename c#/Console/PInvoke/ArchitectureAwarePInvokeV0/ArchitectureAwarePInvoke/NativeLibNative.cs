// 2018-05-17T12:14+08:00
namespace ArchitectureAwarePInvoke
{
    using System;
    using System.Runtime.InteropServices;

    public static unsafe class NativeLibNative
    {
        static NativeLibNative()
        {
            string path;

            if (IntPtr.Size == 4)
                path = "x86/NativeLib.dll";
            else
                path = "x64/NativeLib.dll";

            unsafe
            {
                void* handle = LoadLibrary(path);

                if (handle == null)
                    throw new DllNotFoundException("unable to find the native library: " + path);

                unloader = new LibraryUnloader(handle);
            }
        }

        [DllImport("NativeLib.dll")]
        public static extern void Foo();
        
        [DllImport("kernel32")]
        private unsafe static extern void* LoadLibrary(string dllname);
        
        [DllImport("kernel32")]
        private unsafe static extern void FreeLibrary(void* handle);
        
        private sealed unsafe class LibraryUnloader
        {
            internal LibraryUnloader(void* handle)
            {
                this.handle = handle;
            }
            
            ~LibraryUnloader()
            {
                if (handle != null)
                    FreeLibrary(handle);
            }
            
            private void* handle;
        } // LibraryUnloader
        
        private static readonly LibraryUnloader unloader;
    }
}

// References:
// https://stackoverflow.com/questions/1573724/cpu-architecture-independent-p-invoke-can-the-dllname-or-path-be-dynamic
// https://github.com/squid-box/SevenZipSharp/blob/dev/SevenZip/LibraryManager.cs
