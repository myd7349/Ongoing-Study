using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace MandelbrotSet
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            CompositionTarget.Rendering += CompositionTarget_Rendering;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            Debug.WriteLine($"Window: {ActualWidth}x{ActualHeight}");
            if (ActualWidth <= 0 || ActualHeight <= 0)
                return;

            writeableBitmap_ = new WriteableBitmap(
                (int)ActualWidth,
                (int)ActualHeight,
                96,
                96,
                PixelFormats.Bgr32,
                null);
            image_.Source = writeableBitmap_;
        }

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            MandelbrotSetHelper.Draw(writeableBitmap_);
        }

        private WriteableBitmap writeableBitmap_;
    }
}


// References:
// https://en.wikipedia.org/wiki/Mandelbrot_set
// [WriteableBitmap Class](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.writeablebitmap?view=windowsdesktop-6.0)
// [What is a writeable bitmap?](https://stackoverflow.com/questions/21844151/what-is-a-writeable-bitmap)
// https://github.com/walterlv/walterlv.demo/tree/master/Walterlv.Demo.HighPerformanceBitmap
// [WPF 高性能位图渲染 WriteableBitmap 及其高性能用法示例](https://blog.walterlv.com/post/wpf-high-performance-bitmap-rendering.html)
// [How to edit a WritableBitmap.BackBuffer in non UI thread?](https://stackoverflow.com/questions/9868929/how-to-edit-a-writablebitmap-backbuffer-in-non-ui-thread)
// [Image to fit grid cell size in WPF](https://stackoverflow.com/questions/24698361/image-to-fit-grid-cell-size-in-wpf)
