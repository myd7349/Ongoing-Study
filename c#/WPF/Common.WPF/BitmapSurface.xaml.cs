using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Common.WPF
{
    /// <summary>
    /// Interaction logic for BitmapSurface.xaml
    /// </summary>
    public partial class BitmapSurface : UserControl
    {
        public BitmapSurface()
        {
            InitializeComponent();
        }

        public event EventHandler<BitmapChangedEventArgs> BitmapChanged;

        protected virtual void OnBitmapChanged(BitmapChangedEventArgs e)
        {
            BitmapChanged?.Invoke(this, e);
        }

        private void grid__SizeChanged(object sender, SizeChangedEventArgs e)
        {
            var pixelWidth = (int)grid_.ActualWidth;
            var pixelHeight = (int)grid_.ActualHeight;

            if (pixelWidth > 0 && pixelHeight > 0)
            {
                writeableBitmap_ = new WriteableBitmap(pixelWidth, pixelHeight, 96.0, 96.0, PixelFormats.Pbgra32, null);

                image_.Source = writeableBitmap_;

                OnBitmapChanged(new BitmapChangedEventArgs(writeableBitmap_));
            }
        }

        private WriteableBitmap writeableBitmap_;
    }
}


// References:
// https://github.com/reneschulte/WriteableBitmapEx/blob/master/Source/WriteableBitmapEx/BitmapFactory.cs
