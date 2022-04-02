//#define USE_MMTIMER
#define USE_DISPATCHERTIMER

using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;

using Xceed.Wpf.Toolkit;

#if USE_MMTIMER
using Common;
#endif

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

#if USE_MMTIMER
            timer_ = new MMTimer(Tick, null, null, true)
            {
                Interval = 200,
            };
            timer_.Start();
#elif USE_DISPATCHERTIMER
            timer_ = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(50),
            };
            timer_.Tick += Timer__Tick;
            timer_.Start();
#else
            CompositionTarget.Rendering += CompositionTarget_Rendering;
#endif
        }

#if USE_MMTIMER
        private void Tick(object context)
#elif USE_DISPATCHERTIMER
        private void Timer__Tick(object sender, EventArgs e)
#else
        private void CompositionTarget_Rendering(object sender, EventArgs e)
#endif
        {
            mainWindowViewModel_.Render();
        }

        private void Canvas_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            mainWindowViewModel_.CanvasWidth = (int)e.NewSize.Width;
            mainWindowViewModel_.CanvasHeight = (int)e.NewSize.Height;

            image_.Source = mainWindowViewModel_.CanvasBitmap;
        }

#if USE_MMTIMER
        private MMTimer timer_;
#elif USE_DISPATCHERTIMER
        DispatcherTimer timer_;
#endif
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
