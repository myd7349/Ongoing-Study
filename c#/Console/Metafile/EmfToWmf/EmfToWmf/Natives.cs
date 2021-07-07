namespace EmfToWmf
{
    using System;
    using System.Runtime.InteropServices;

    static class Natives
    {
        public static int MM_ISOTROPIC = 7;
        public static int MM_ANISOTROPIC = 8;

        [Flags]
        public enum EmfToWmfBitsFlags
        {
            EmfToWmfBitsFlagsDefault = 0x00000000,
            EmfToWmfBitsFlagsEmbedEmf = 0x00000001,
            EmfToWmfBitsFlagsIncludePlaceable = 0x00000002,
            EmfToWmfBitsFlagsNoXORClip = 0x00000004
        }

        [DllImport("gdiplus.dll", SetLastError = true)]
        public static extern uint GdipEmfToWmfBits(IntPtr hEmf, uint bufferSize,
            byte[] buffer, int mappingMode, EmfToWmfBitsFlags flags);

        [DllImport("gdi32.dll")]
        public static extern IntPtr SetMetaFileBitsEx(uint bufferSize, byte[] buffer);

        [DllImport("gdi32.dll")]
        public static extern IntPtr CopyMetaFile(IntPtr hWmf, string filename);

        [DllImport("gdi32.dll")]
        public static extern bool DeleteMetaFile(IntPtr hWmf);

        [DllImport("gdi32.dll")]
        public static extern bool DeleteEnhMetaFile(IntPtr hEmf);
    }
}
