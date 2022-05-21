using System;
using System.Windows.Media.Imaging;

using Common;

namespace SkiaSharp.WPF
{
    public class SKSurfaceContext : DisposableBase
    {
        public SKSurfaceContext(WriteableBitmap bitmap)
        {
            bitmap_ = bitmap ?? throw new ArgumentNullException(nameof(bitmap));

            bitmap_.Lock();

            var info = new SKImageInfo(bitmap.PixelWidth, bitmap.PixelHeight, SKImageInfo.PlatformColorType, SKAlphaType.Premul);
            Surface = SKSurface.Create(info, bitmap.BackBuffer, bitmap.BackBufferStride);
        }

        public SKSurface Surface { get; }

        public SKCanvas Canvas => Surface?.Canvas;

        public static SKSurfaceContext Create(WriteableBitmap bitmap)
        {
            return new SKSurfaceContext(bitmap);
        }

        protected override void DisposeManaged()
        {
            Surface.Dispose();

            bitmap_.Unlock();
        }

        private WriteableBitmap bitmap_;
    }
}
