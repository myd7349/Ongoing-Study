using System;
using System.Windows;
using System.Windows.Media.Imaging;

namespace Common.WPF
{
    public static class WriteableBitmapExtension
    {
        public static void AddDirtyRect(this WriteableBitmap writeableBitmap, int left, int top, int width, int height)
        {
            writeableBitmap.AddDirtyRect(new Int32Rect(left, top, width, height));
        }

        public static Int32Rect AdjustRect(this WriteableBitmap writeableBitmap, int left, int top, int width, int height)
        {
            return writeableBitmap.AdjustRect(new Int32Rect(left, top, width, height));
        }

        public static Int32Rect AdjustRect(this WriteableBitmap writeableBitmap, Int32Rect rect)
        {
            if (writeableBitmap == null)
                throw new ArgumentNullException(nameof(writeableBitmap));

            if (rect.X < 0)
                rect.X = 0;

            if (rect.X >= writeableBitmap.PixelWidth)
                rect.X = writeableBitmap.PixelWidth - 1;

            if (rect.Width > writeableBitmap.PixelWidth - rect.X)
                rect.Width = writeableBitmap.PixelWidth - rect.X;

            if (rect.Y < 0)
                rect.Y = 0;

            if (rect.Y >= writeableBitmap.PixelHeight)
                rect.Y = writeableBitmap.PixelHeight - 1;

            if (rect.Height > writeableBitmap.PixelHeight - rect.Y)
                rect.Height = writeableBitmap.PixelHeight - rect.Y;

            return rect;
        }

        public static void AddDirtyRectAutoAdjust(this WriteableBitmap writeableBitmap, int left, int top, int width, int height)
        {
            var adjustedRect = writeableBitmap.AdjustRect(left, top, width, height);
            writeableBitmap.AddDirtyRect(adjustedRect);
        }

        public static void AddDirtyRectAutoAdjust(this WriteableBitmap writeableBitmap, Int32Rect rect)
        {
            var adjustedRect = writeableBitmap.AdjustRect(rect);
            writeableBitmap.AddDirtyRect(adjustedRect);
        }
    }
}
