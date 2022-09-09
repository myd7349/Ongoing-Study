using System;
using System.Windows.Media.Imaging;

namespace Common.WPF
{
    public class BitmapChangedEventArgs : EventArgs
    {
        public BitmapChangedEventArgs(WriteableBitmap writeableBitmap)
        {
            Bitmap = writeableBitmap ?? throw new ArgumentNullException(nameof(writeableBitmap));
        }

        public WriteableBitmap Bitmap { get; }
    }
}
