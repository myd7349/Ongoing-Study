using System;
using System.Windows.Media.Imaging;

using Common;
using Common.WPF;

namespace SkiaSharp.WPF
{
    public class SKSurfaceContext : DisposableBase
    {
        public SKSurfaceContext(WriteableBitmap bitmap)
        {
            Bitmap = bitmap ?? throw new ArgumentNullException(nameof(bitmap));

            Bitmap.Lock();

            var info = new SKImageInfo(bitmap.PixelWidth, bitmap.PixelHeight, SKImageInfo.PlatformColorType, SKAlphaType.Premul);
            Surface = SKSurface.Create(info, bitmap.BackBuffer, bitmap.BackBufferStride);
        }

        public WriteableBitmap Bitmap { get; }

        public SKSurface Surface { get; }

        public SKCanvas Canvas => Surface?.Canvas;

        public void Invalidate()
        {
            Invalidate(0, 0, Bitmap.PixelWidth, Bitmap.PixelHeight);
        }

        public void Invalidate(int x, int y, int width, int height)
        {
            Bitmap.AddDirtyRectAutoAdjust(x, y, width, height);
        }

        public static SKSurfaceContext Create(WriteableBitmap bitmap)
        {
            return new SKSurfaceContext(bitmap);
        }

        protected override void DisposeManaged()
        {
            Surface.Dispose();

            Bitmap.Unlock();
        }
    }
}
