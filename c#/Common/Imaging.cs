namespace Common.Auxiliary.Drawing
{
    using System;
    using System.Drawing.Imaging;

    public static class Imaging
    {
        public static ImageFormat GetImageFormat(string fileExtension)
        {
            if (string.IsNullOrEmpty(fileExtension))
                throw new ArgumentException("Invalid file extension");

            if (fileExtension[0] != '.')
                fileExtension = "." + fileExtension;

            switch (fileExtension.ToLower())
            {
                case @".bmp": return ImageFormat.Bmp;
                case @".emf": return ImageFormat.Emf;
                case @".gif": return ImageFormat.Gif;
                case @".ico": return ImageFormat.Icon;
                case @".jpg":
                case @".jpeg": return ImageFormat.Jpeg;
                case @".png": return ImageFormat.Png;
                case @".tif":
                case @".tiff": return ImageFormat.Tiff;
                case @".wmf": return ImageFormat.Wmf;
                default: throw new NotImplementedException();
            }
        }
    }
}


// References:
// https://stackoverflow.com/questions/1337750/get-imageformat-from-file-extension

