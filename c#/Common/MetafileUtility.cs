namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.IO;
    using System.Runtime.InteropServices;

    public static class MetafileUtility
    {
        public static void MetafileToWMF(ref Metafile metafile, string outputWmfFilepath)
        {
            if (metafile == null)
                throw new ArgumentNullException("metafile");

            if (string.IsNullOrWhiteSpace(outputWmfFilepath))
                throw new ArgumentException("outputWmfFilepath");

            var hEmf = GetMetafileHandle(ref metafile);

            var bufferSize = GdipEmfToWmfBits(hEmf, 0, null, MM_ANISOTROPIC,
                EmfToWmfBitsFlags.EmfToWmfBitsFlagsDefault);

            byte[] buffer = new byte[bufferSize];
            GdipEmfToWmfBits(hEmf, bufferSize, buffer, MM_ANISOTROPIC,
                EmfToWmfBitsFlags.EmfToWmfBitsFlagsDefault);

            var hWmf = SetMetaFileBitsEx(bufferSize, buffer);
            CopyMetaFile(hWmf, outputWmfFilepath);
            DeleteMetaFile(hWmf);
        }

        public static Bitmap MetafileToBitmap(Metafile metafile)
        {
            if (metafile == null)
                throw new ArgumentNullException("metafile");

            var bitmap = new Bitmap(metafile.Width, metafile.Height);
            bitmap.SetResolution(metafile.HorizontalResolution, metafile.VerticalResolution);
            using (var graphics = Graphics.FromImage(bitmap))
                graphics.DrawImage(metafile, 0, 0);

            return bitmap;
        }

        public static Metafile BitmapToMetafile(Bitmap bitmap)
        {
            if (bitmap == null)
                throw new ArgumentNullException("bitmap");

            using (var graphics = Graphics.FromImage(bitmap))
            {
                var hdc = graphics.GetHdc();

                var metafile = new Metafile(hdc, EmfType.EmfOnly);
                using (var canvas = Graphics.FromImage(metafile))
                    graphics.DrawImage(bitmap, 0, 0);

                graphics.ReleaseHdc(hdc);

                return metafile;
            }
        }

        public static MemoryStream BitmapToMetafileMemoryStream(Bitmap bitmap)
        {
            if (bitmap == null)
                throw new ArgumentNullException("bitmap");

            using (var graphics = Graphics.FromImage(bitmap))
            {
                var hdc = graphics.GetHdc();

                var memoryStream = new MemoryStream();
                var metafile = new Metafile(memoryStream, hdc);
                using (var canvas = Graphics.FromImage(metafile))
                    canvas.DrawImage(bitmap, 0, 0);

                graphics.ReleaseHdc(hdc);

                return memoryStream;
            }
        }

        public static Metafile Rotate(Metafile originalMetafile, int degrees, string filePath = null)
        {
            Debug.Assert(originalMetafile != null);

            Metafile metafile = null;

#if false
            MemoryStream memoryStream = null;

            if (string.IsNullOrEmpty(filePath))
            {
                memoryStream = new MemoryStream();
                metafile = new Metafile(memoryStream);
            }
            else
            {
                metafile = new Metafile(filePath);
            }
#elif false
            // OutOfMemoryException
            // [Create graphics from Metafile error "out of memory"](https://stackoverflow.com/questions/27097700/create-graphics-from-metafile-error-out-of-memory)
            using (var graphics = Graphics.FromImage(originalMetafile))
            {
                var referenceHdc = graphics.GetHdc();
                metafile = new Metafile(referenceHdc, EmfType.EmfPlusDual);
            }
#elif false
            var bitmap = new Bitmap(1, 1);
            bitmap.SetResolution(originalMetafile.HorizontalResolution, originalMetafile.VerticalResolution);

            using (var graphics = Graphics.FromImage(bitmap))
            {
                var referenceHdc = graphics.GetHdc();
                var originalMetafileType = originalMetafile.GetMetafileHeader().Type;
                metafile = new Metafile(referenceHdc, MetafileTypeToEmfType(originalMetafileType));
                graphics.ReleaseHdc(referenceHdc);
            }

            bitmap.Dispose();
#else
            using (var graphics = Graphics.FromHwnd(IntPtr.Zero))
            {
                var referenceHdc = graphics.GetHdc();
                var originalMetafileType = originalMetafile.GetMetafileHeader().Type;
                metafile = new Metafile(referenceHdc, MetafileTypeToEmfType(originalMetafileType));
                graphics.ReleaseHdc(referenceHdc);
            }
#endif

            switch (degrees)
            {
                case 90:
                case 270:
                    using (var graphics = Graphics.FromImage(metafile))
                    {
                        graphics.TranslateTransform(originalMetafile.Width / 2, originalMetafile.Height / 2);
                        graphics.RotateTransform(degrees);

                        var enumerateMetafileHelper = new EnumerateMetafileHelper(originalMetafile);
                        graphics.EnumerateMetafile(originalMetafile, Point.Empty,
                            enumerateMetafileHelper.EnumerateMetafileCallback);
                    }
                    break;
                case 180:
                    using (var graphics = Graphics.FromImage(metafile))
                    {
                        graphics.TranslateTransform(originalMetafile.Width / 2, originalMetafile.Height / 2);
                        graphics.RotateTransform(degrees);

                        var enumerateMetafileHelper = new EnumerateMetafileHelper(originalMetafile);
                        graphics.EnumerateMetafile(originalMetafile, Point.Empty,
                            enumerateMetafileHelper.EnumerateMetafileCallback);
                    }
                    break;
                default:
                    throw new NotImplementedException();
            }

#if false
            memoryStream?.Dispose();
#endif

            return metafile;
        }

        public static Metafile CopyMetafile(ref Metafile metafile)
        {
            return CopyMetafile(ref metafile, null);
        }

        public static Metafile CopyMetafile(ref Metafile metafile, string filePath)
        {
            var hEmf = GetMetafileHandle(ref metafile);
            return new Metafile(CopyEnhMetaFile(hEmf, filePath), true);
        }

        // Metafile.GetHenhmetafile is just a wrapper of GdipGetHemfFromMetafile:
        // https://github.com/dotnet/runtime/blob/78c6505cffe2558b036fbe44cd27038affbb6cce/src/libraries/System.Drawing.Common/src/System/Drawing/Imaging/Metafile.Windows.cs#L379-L383
        // and according to:
        // http://www.jose.it-berater.org/gdiplus/reference/flatapi/graphics/gdipgethemffrommetafile.htm
        // > GdipGetHemfFromMetafile:
        // > This method sets the Metafile object to an invalid state. The user is responsible for calling DeleteEnhMetafile,
        // > to delete the Windows handle.
        // If we want to get a native handle of Metafile object without invalidate the original Metafile object, we should
        // COPY the metafile instead:
        // Metafile.CopyMetaFile(string path);
        //     var enhMetafileHandle = metafile_.CopyMetaFile(null); // Copy to memory.
        //     Gdi32.DeleteEnhMetaFile(enhMetafileHandle);
        // Unfortunately, Metafile class doesn't provide a wrapper method for CopyMetaFileW function.
        //
        // Can we write an extension method like this?
        // public static IntPtr GetHenhmetafileEx(this Metafile metafile)
        // {
        //     var handle = metafile.GetHenhmetafile();
        //     metafile = new Metafile(handle, false);
        //     return handle;
        // }
        // [How can I get an extension method to change the original object?](https://stackoverflow.com/questions/2326734/how-can-i-get-an-extension-method-to-change-the-original-object)
        public static IntPtr GetMetafileHandle(ref Metafile metafile)
        {
            if (metafile == null)
                throw new ArgumentNullException("metafile");

            var hEmf = metafile.GetHenhmetafile();
            metafile = new Metafile(hEmf, true);

            return hEmf;
        }

        public static EmfType MetafileTypeToEmfType(MetafileType metafileType)
        {
            switch (metafileType)
            {
                case MetafileType.Emf:
                    return EmfType.EmfOnly;
                case MetafileType.EmfPlusOnly:
                    return EmfType.EmfPlusOnly;
                case MetafileType.EmfPlusDual:
                    return EmfType.EmfPlusDual;
                default:
                    throw new ArgumentException("metafileType");
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct PLACEABLEMETAHEADER
        {
            public uint Key; // Magic number (always 9AC6CDD7h)
            public ushort Handle; // Metafile HANDLE number (always 0) /
            public short Left; // Left coordinate in metafile units /
            public short Top; // Top coordinate in metafile units /
            public short Right; // Right coordinate in metafile units /
            public short Bottom; // Bottom coordinate in metafile units /
            public ushort Inch; // Number of metafile units per inch /
            public uint Reserved; // Reserved (always 0) /
            public ushort Checksum; // Checksum value for previous 10 WORDs */
        }

        //private static int MM_ISOTROPIC = 7;
        private static int MM_ANISOTROPIC = 8;

        [Flags]
        private enum EmfToWmfBitsFlags
        {
            EmfToWmfBitsFlagsDefault = 0x00000000,
            EmfToWmfBitsFlagsEmbedEmf = 0x00000001,
            EmfToWmfBitsFlagsIncludePlaceable = 0x00000002,
            EmfToWmfBitsFlagsNoXORClip = 0x00000004
        }

        [DllImport("gdiplus.dll", SetLastError = true)]
        private static extern uint GdipEmfToWmfBits(IntPtr hEmf, uint bufferSize,
            byte[] buffer, int mappingMode, EmfToWmfBitsFlags flags);

        [DllImport("gdi32.dll")]
        private static extern IntPtr SetMetaFileBitsEx(uint bufferSize, byte[] buffer);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CopyMetaFile(IntPtr hWmf, string filename);

        [DllImport("gdi32.dll")]
        private static extern bool DeleteMetaFile(IntPtr hWmf);

        [DllImport("gdi32.dll")]
        private static extern IntPtr CopyEnhMetaFile(IntPtr hEmf, string filename);

        [DllImport("gdi32.dll")]
        private static extern bool DeleteEnhMetaFile(IntPtr hEmf);

        public static byte[] GetMetafileRawBytes(Metafile metafile)
        {
            byte[] data = null;

            var metafileHeader = metafile.GetMetafileHeader();
            var handle = metafile.GetHenhmetafile();

            try
            {
                var flag = EmfToWmfBitsFlags.EmfToWmfBitsFlagsIncludePlaceable;

                uint dataSize = GdipEmfToWmfBits(handle, 0, null, MM_ANISOTROPIC, flag);

                if (dataSize == 0) // Not Support EmfToWmfBitsFlagsIncludePlaceable
                {
                    flag = EmfToWmfBitsFlags.EmfToWmfBitsFlagsDefault;
                    dataSize = GdipEmfToWmfBits(handle, 0, null, MM_ANISOTROPIC, flag);
                }

                data = new byte[dataSize];

                GdipEmfToWmfBits(handle, dataSize, data, MM_ANISOTROPIC, flag);

                if (flag == EmfToWmfBitsFlags.EmfToWmfBitsFlagsDefault) // Add PlaceableMetaHeader to Byte Array
                {
                    var placeableList = new List<byte>();

                    var placeable = new PLACEABLEMETAHEADER();

                    placeable.Key = 0x9AC6CDD7; // Fix
                    placeable.Left = (short)metafileHeader.Bounds.Left;
                    placeable.Top = (short)metafileHeader.Bounds.Top;
                    placeable.Right = (short)metafileHeader.Bounds.Width;
                    placeable.Bottom = (short)metafileHeader.Bounds.Height;
                    placeable.Inch = 1440; // Fix?!?!?!?!

                    placeable.Checksum = 0;
                    placeable.Checksum ^= (ushort)(placeable.Key & 0x0000FFFF);
                    placeable.Checksum ^= (ushort)((placeable.Key & 0xFFFF0000) >> 16);
                    placeable.Checksum ^= (ushort)placeable.Handle;
                    placeable.Checksum ^= (ushort)placeable.Left;
                    placeable.Checksum ^= (ushort)placeable.Top;
                    placeable.Checksum ^= (ushort)placeable.Right;
                    placeable.Checksum ^= (ushort)placeable.Bottom;
                    placeable.Checksum ^= (ushort)placeable.Inch;
                    placeable.Checksum ^= (ushort)(placeable.Reserved & 0x0000FFFF);
                    placeable.Checksum ^= (ushort)((placeable.Reserved & 0xFFFF0000) >> 16);

                    placeableList.AddRange(StructHelpers.StructToBytes(placeable));
                    placeableList.AddRange(data);

                    data = placeableList.ToArray();
                }
            }
            finally
            {
                DeleteEnhMetaFile(handle);
            }

            return data;
        }
    }

    internal class EnumerateMetafileHelper
    {
        public EnumerateMetafileHelper(Metafile metafile)
        {
            metafile_ = metafile;
        }

        public bool EnumerateMetafileCallback(EmfPlusRecordType recordType, int flags, int dataSize, IntPtr data, PlayRecordCallback callbackData)
        {
            byte[] dataArray = null;
            if (data != IntPtr.Zero)
            {
                // Copy the unmanaged record to a managed byte buffer 
                // that can be used by PlayRecord.
                dataArray = new byte[dataSize];
                Marshal.Copy(data, dataArray, 0, dataSize);
            }

            metafile_.PlayRecord(recordType, flags, dataSize, dataArray);

            return true;
        }

        private Metafile metafile_;
    }
}


// References:
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Drawing.Common/src/System/Drawing/Imaging/Metafile.cs
// [How to save a MS Chart in WMF format and insert in the PDF iTextSharp](https://stackoverflow.com/questions/43276550/how-to-save-a-ms-chart-in-wmf-format-and-insert-in-the-pdf-itextsharp)
// [Convert an image into WMF with .NET?](https://stackoverflow.com/questions/5270763/convert-an-image-into-wmf-with-net)
// [How do I resize (shrink) an EMF (Metafile) in .Net?](https://stackoverflow.com/questions/12098924/how-do-i-resize-shrink-an-emf-metafile-in-net)
// [EMF to PDF as raster image](https://tallcomponents.com/code-samples/emf-to-pdf-as-raster-image/)
/*
EMF to PDF as raster image
Step 1:
static Bitmap EMF2Bitmap(string file_name)
{
    using (Metafile emf = new Metafile(file_name))
    {
        Bitmap bmp = new Bitmap(emf.Width, emf.Height);

        using (Graphics g = Graphics.FromImage(bmp))
        {
            g.DrawImage(emf, 0, 0);
            return bmp;
        }
    }
}
Step 2:
static void Bitmap2Pdf(System.Drawing.Bitmap bmp, string file_name)
{
    ImageShape img = new ImageShape(bmp);
    Document document = new Document();
    Page page = new Page(img.Width, img.Height);

    page.VisualOverlay.Add(img);
    document.Pages.Add(page);
    using (FileStream fs = new FileStream(file_name, FileMode.Create, FileAccess.Write))
    {
        document.Write(fs);
    }
}
Together:
static void Main(string[] args)
{
    // http://stackoverflow.com/questions/10147293/how-to-display-windows-metafile
    string input = @"D:\github\EMFToBitmap\sample.emf";
    string output = @"D:\github\EMFToBitmap\sample.pdf";

    Bitmap bmp = EMF2Bitmap(input);
    Bitmap2Pdf(bmp, output);
}
 */
// [Is there a way to write System.Drawing.Graphics to PDF from C#?](https://stackoverflow.com/questions/7439699/is-there-a-way-to-write-system-drawing-graphics-to-pdf-from-c)
// [GDI+ / C#: How to save an image as EMF?](https://stackoverflow.com/questions/152729/gdi-c-how-to-save-an-image-as-emf)
// https://github.com/dahall/Vanara/blob/master/PInvoke/Gdi32/WinGdi.Metafile.cs
// [GDI+ / C#: How to save an image as EMF?](https://stackoverflow.com/questions/152729/gdi-c-how-to-save-an-image-as-emf)
// [Make and use a metafile in C#](http://csharphelper.com/blog/2016/04/make-use-metafile-c/)
// > A metafile is a drawing that doesn’t just contain the pixels in an image.
// > Instead it contains a record of the commands used to produce a drawing so
// > you can rerun those commands later.
// > To create a new metafile, you need a graphics device handle. To get one, 
// > the code create a 16×16 pixel bitmap. The bitmap’s size isn’t important;
// > the code really just needs to use it to get a graphics device handle.
// [How to make emf file dpi aware](https://stackoverflow.com/questions/54488961/how-to-make-emf-file-dpi-aware)
