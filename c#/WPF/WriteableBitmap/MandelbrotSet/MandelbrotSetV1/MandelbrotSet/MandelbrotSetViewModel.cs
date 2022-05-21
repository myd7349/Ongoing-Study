//#define USE_SETPIXEL

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using MvvmHelpers;

using Common;


namespace MandelbrotSet
{
    public class MandelbrotSetViewModel : BaseViewModel
    {
        public WriteableBitmap CanvasBitmap
        {
            get => canvasBitmap_;
            private set => SetProperty(ref canvasBitmap_, value);
        }

        public int CanvasWidth
        {
            get => canvasWidth_;
            set => SetProperty(ref canvasWidth_, value, onChanged: OnCanvasSizeChanged);
        }

        public int CanvasHeight
        {
            get => canvasHeight_;
            set => SetProperty(ref canvasHeight_, value, onChanged: OnCanvasSizeChanged);
        }

        public Color BackColor
        {
            get => backColor_;
            set => SetProperty(ref backColor_, value, onChanged: Reset);
        }

        public int IterationCount
        {
            get => iterationCount_;
            set => SetProperty(ref iterationCount_, value);
        }

        public long RenderingTimeInMilliseconds
        {
            get => renderingTime_;
            set => SetProperty(ref renderingTime_, value);
        }

        public long MaximumRenderingTimeInMilliseconds
        {
            get => maximumRenderingTime_;
            set => SetProperty(ref maximumRenderingTime_, value);
        }

        public long MinimumRenderingTimeInMilliseconds
        {
            get => minimumRenderingTime_;
            set => SetProperty(ref minimumRenderingTime_, value);
        }

        public void Render()
        {
            if (canvasBitmap_ == null)
                return;

            var stopwatch = Stopwatch.StartNew();

#if USE_SETPIXEL
            using (var context = canvasBitmap_.GetBitmapContext())
                RenderImpl();
#else
            try
            {
                canvasBitmap_.Lock();

                RenderImpl(canvasBitmap_.BackBuffer, canvasBitmap_.BackBufferStride);

                canvasBitmap_.AddDirtyRect(new Int32Rect(0, 0, CanvasWidth, CanvasHeight));
            }
            finally
            {
                canvasBitmap_.Unlock();
            }
#endif

            RenderingTimeInMilliseconds = stopwatch.ElapsedMilliseconds;

            if (RenderingTimeInMilliseconds > MaximumRenderingTimeInMilliseconds)
                MaximumRenderingTimeInMilliseconds = RenderingTimeInMilliseconds;
            else if (RenderingTimeInMilliseconds < MinimumRenderingTimeInMilliseconds)
                MinimumRenderingTimeInMilliseconds = RenderingTimeInMilliseconds;
        }

        private void OnCanvasSizeChanged()
        {
            CanvasBitmap = null;

            IsBusy = true;

            if (canvasWidth_ > 1 && canvasHeight_ > 1)
            {
                Debug.WriteLine($"Canvas size: {CanvasWidth}x{CanvasHeight}");

#if USE_SETPIXEL
                CanvasBitmap = BitmapFactory.New(canvasWidth_, canvasHeight_);
#else
                CanvasBitmap = new WriteableBitmap(
                    canvasWidth_, canvasHeight_,
                    96, 96, PixelFormats.Bgr32,
                    null);
#endif

                Reset();
            }

            IsBusy = false;
        }

        private void Reset()
        {
            Debug.Assert(CanvasBitmap != null);

            CanvasBitmap.Clear(BackColor);

            points_ = new Point[canvasHeight_, canvasWidth_];
            inSet_ = new bool[canvasHeight_, canvasWidth_];
            inSet_.Fill(true);

            IterationCount = 0;
        }

#if USE_SETPIXEL
        private void RenderImpl()
#else
        private unsafe void RenderImpl(IntPtr buffer, int stride)
#endif
        {
            if (iterationCount_ >= MaxIterations)
                return;

            IsBusy = true;

            // Real and imaginary bounds of the complex plane.
            double realMin = -2.1;
            double realMax = 1.0;
            double imgMin = -1.3;
            double imgMax = 1.3;

            // Factors for mapping from image coordinates to coordinates on the complex plane.
            double realFactor = (realMax - realMin) / (CanvasWidth - 1);
            double imgFactor = (imgMax - imgMin) / (CanvasHeight - 1);

            // Compute whether each point lies in the Mandelbrot set.
            for (int row = 0; row < CanvasHeight; ++row)
            {
#if !USE_SETPIXEL
                // Obtain a pointer to the bitmap bits for the current row.
                var destPixel = buffer + row * stride;
#endif

                // Convert from image coordinate to coordinate on the complex plane.
                double y0 = imgMax - (row * imgFactor);

                var red = (byte)((iterationCount_ % 64) * 4);

                for (int col = 0; col < CanvasWidth; ++col)
                {
                    // Convert from image coordinate to coordinate on the complex plane.
                    double x0 = realMin + col * realFactor;

                    double x;
                    double y;

                    if (iterationCount_ == 0)
                    {
                        x = x0;
                        y = y0;
                    }
                    else
                    {
                        x = points_[row, col].X;
                        y = points_[row, col].Y;
                    }

                    double x_sq = x * x;
                    double y_sq = y * y;

                    var inSet = (x_sq + y_sq) < 4;

                    if (inSet_[row, col] != inSet)
                    {
#if USE_SETPIXEL
                        if (inSet)
                            canvasBitmap_.SetPixel(col, row, Colors.Black);
                        else
                            canvasBitmap_.SetPixel(col, row, red, 0, 0);
#else
                        if (inSet)
                            *(int*)destPixel = 0;
                        else
                            *(int*)destPixel = red << 16;
#endif

                        inSet_[row, col] = inSet;
                    }

                    points_[row, col].X = x_sq - y_sq + x0;
                    points_[row, col].Y = 2 * x * y + y0;

#if !USE_SETPIXEL
                    destPixel += 4;
#endif
                }
            }

            IterationCount = IterationCount + 1;

            IsBusy = false;
        }

        // The maximum number of iterations to perform on each point.
        public const int MaxIterations = 1000;

        private int canvasWidth_;
        private int canvasHeight_;
        private WriteableBitmap canvasBitmap_;
        private Color backColor_ = Colors.Black;
        private Point[,] points_;
        private bool[,] inSet_;
        private int iterationCount_ = 0;
        private long renderingTime_;
        private long maximumRenderingTime_;
        private long minimumRenderingTime_ = long.MaxValue;
    }
}


// References:
// https://www.bilibili.com/video/BV1q7411A7Rz/
// [The Edge of Infinity - Mandelbrot Fractal Zoom (e2011) (4k 60fps)](https://www.youtube.com/watch?v=u1pwtSBTnPU)
// ["上帝的指纹" - 走进无限美妙的曼德博集合](https://zhuanlan.zhihu.com/p/52303089)
// [What is the Mandelbrot set?](https://plus.maths.org/content/what-mandelbrot-set)
// [Walkthrough: Removing Work from a User-Interface Thread](https://docs.microsoft.com/en-us/cpp/parallel/concrt/walkthrough-removing-work-from-a-user-interface-thread?view=msvc-160)
// https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/parallel/concrt/walkthrough-removing-work-from-a-user-interface-thread.md
// https://doc.qt.io/qt-5/qtcore-threads-mandelbrot-example.html
// https://github.com/qt/qtbase/tree/dev/examples/corelib/threads/mandelbrot
// https://www.boost.org/doc/libs/1_56_0/libs/gil/example/mandelbrot.cpp
// https://github.com/FrankHB/YEGE/tree/master/MandelbrotSet
