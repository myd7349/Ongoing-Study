namespace Common.Auxiliary.Drawing
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

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

        public static Rectangle ImageRectangleFromSizeMode(Image image, Rectangle rectangle, PictureBoxSizeMode mode, Padding padding)
        {
            Rectangle result = rectangle.Deflate(padding);
            if (image != null)
            {
                switch (mode)
                {
                    case PictureBoxSizeMode.Normal:
                    case PictureBoxSizeMode.AutoSize:
                        // Use image's size rather than client size.
                        result.Size = image.Size;
                        break;

                    case PictureBoxSizeMode.StretchImage:
                        // Do nothing, was initialized to the available dimensions.
                        break;

                    case PictureBoxSizeMode.CenterImage:
                        // Center within the available space.
                        result.X += (result.Width - image.Width) / 2;
                        result.Y += (result.Height - image.Height) / 2;
                        result.Size = image.Size;
                        break;

                    case PictureBoxSizeMode.Zoom:
                        Size imageSize = image.Size;
                        float ratio = Math.Min((float)rectangle.Width / (float)imageSize.Width, (float)rectangle.Height / (float)imageSize.Height);
                        result.Width = (int)(imageSize.Width * ratio);
                        result.Height = (int)(imageSize.Height * ratio);
                        result.X = (rectangle.Width - result.Width) / 2;
                        result.Y = (rectangle.Height - result.Height) / 2;
                        break;

                    default:
                        throw new ArgumentException("Unsupported PictureBoxSizeMode value: " + mode);
                }
            }

            return result;
        }
    }
}


// References:
// https://stackoverflow.com/questions/1337750/get-imageformat-from-file-extension
// https://github.com/dotnet/winforms/blob/a8905ab4ba4981db444644a2b028fbff92f41893/src/System.Windows.Forms/src/System/Windows/Forms/PictureBox.cs#L336-L376

