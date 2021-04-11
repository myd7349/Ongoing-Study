namespace MarshalCppClass
{
    using PInvoke;

    class WinNTDLLImporter : NativeDLLImporter
    {
        public override void LoadLibrary(string path)
        {
            handle_ = Kernel32.LoadLibrary(path);
        }

        public override void FreeLibrary()
        {
            // Thanks to Kernel32.SafeLibraryHandle, we
            // will do nothing here.
        }

        private Kernel32.SafeLibraryHandle handle_;
    }
}
