using System;
using System.Drawing;
using System.IO;
using System.Windows.Media.Imaging;

namespace Common.WPF.Imaging
{
    public static class ImageHelper
    {
        public static void Save(this BitmapSource bitmap, ImageFormat format, Stream stream)
        {
            var bitmapEncoder = CreateBitmapEncoder(format);
            bitmapEncoder.Frames.Add(BitmapFrame.Create(bitmap));
            bitmapEncoder.Save(stream);
        }

        public static void Save(this BitmapSource bitmap, string filePath)
        {
            var fileExtension = Path.GetExtension(filePath);
            var format = GetImageFormat(fileExtension);
            using (var stream = File.Create(filePath))
                bitmap.Save(format, stream);
        }

        public static ImageFormat GetImageFormat(string fileExtension)
        {
            if (string.IsNullOrEmpty(fileExtension))
                throw new ArgumentException("Invalid file extension");

            if (fileExtension[0] != '.')
                fileExtension = "." + fileExtension;

            switch (fileExtension.ToLower())
            {
                case ".bmp":
                case ".dib": return ImageFormat.Bmp;
                case ".gif": return ImageFormat.Gif;
                case ".jpg":
                case ".jpeg": return ImageFormat.Jpeg;
                case ".png": return ImageFormat.Png;
                case ".tif":
                case ".tiff": return ImageFormat.Tiff;
                default: throw new NotImplementedException();
            }
        }

        public static BitmapEncoder CreateBitmapEncoder(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat.Bmp:
                    return new BmpBitmapEncoder();
                case ImageFormat.Gif:
                    return new GifBitmapEncoder();
                case ImageFormat.Jpeg:
                    return new JpegBitmapEncoder();
                case ImageFormat.Png:
                    return new PngBitmapEncoder();
                case ImageFormat.Tiff:
                    return new TiffBitmapEncoder();
                default: throw new NotImplementedException();
            }
        }

        public static Bitmap ToBitmap(this BitmapSource bitmapSource, ImageFormat format = ImageFormat.Png)
        {
            if (bitmapSource == null)
                throw new ArgumentNullException(nameof(bitmapSource));

            using (var memoryStream = new MemoryStream())
            {
                bitmapSource.Save(format, memoryStream);
                return new Bitmap(memoryStream);
            }
        }
    }
}


// References:
// [Imaging Overview](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/graphics-multimedia/imaging-overview?view=netframeworkdesktop-4.8)
// [WPF Image控件中的ImageSource与Bitmap的互相转换](https://www.cnblogs.com/tianma3798/p/4520033.html)
// [Interop Between WPF and GDI+](https://social.msdn.microsoft.com/Forums/vstudio/en-US/de119df2-7100-413f-94ca-676c387406e1/interop-between-wpf-and-gdi?forum=wpf)
// [Load a WPF BitmapImage from a System.Drawing.Bitmap](https://stackoverflow.com/questions/94456/load-a-wpf-bitmapimage-from-a-system-drawing-bitmap)
// [Convert ImageSource to BitmapImage - WPF](https://stackoverflow.com/questions/920517/convert-imagesource-to-bitmapimage-wpf)
// [How to display Windows Metafile?](https://stackoverflow.com/questions/10147293/how-to-display-windows-metafile)
