using System;
using System.Windows;
using System.Windows.Media.Imaging;

namespace MandelbrotSet
{
    static class MandelbrotSetHelper
    {
        public static void Draw(WriteableBitmap writeableBitmap)
        {
            if (writeableBitmap == null)
                return;

            if (writeableBitmap.Width <= 1 || writeableBitmap.Height <= 1)
                return;

            try
            {
                writeableBitmap.Lock();

                var width = (int)writeableBitmap.Width;
                var height = (int)writeableBitmap.Height;

                Draw(writeableBitmap.BackBuffer,
                    width, height,
                    writeableBitmap.BackBufferStride);

                writeableBitmap.AddDirtyRect(
                    new Int32Rect(0, 0, width, height));
            }
            finally
            {
                writeableBitmap.Unlock();
            }
        }

        private static unsafe void Draw(IntPtr buffer, int width, int height, int stride)
        {
            // Real and imaginary bounds of the complex plane.
            double realMin = -2.1;
            double realMax = 1.0;
            double imgMin = -1.3;
            double imgMax = 1.3;

            // Factors for mapping from image coordinates to coordinates on the complex plane.
            double realFactor = (realMax - realMin) / (width - 1);
            double imgFactor = (imgMax - imgMin) / (height - 1);

            // The maximum number of iterations to perform on each point.
            const int MaxIterations = 1000;

            // Compute whether each point lies in the Mandelbrot set.
            for (int row = 0; row < height; ++row)
            {
                // Obtain a pointer to the bitmap bits for the current row.
                var destPixel = buffer + row * stride;

                // Convert from image coordinate to coordinate on the complex plane.
                double y0 = imgMax - (row * imgFactor);

                for (double col = 0; col < width; ++col)
                {
                    // Convert from image coordinate to coordinate on the complex plane.
                    double x0 = realMin + col * realFactor;

                    double x = x0;
                    double y = y0;

                    int iter = 0;
                    double x_sq, y_sq;
                    while (iter < MaxIterations && ((x_sq = x * x) + (y_sq = y * y) < 4))
                    {
                        double temp = x_sq - y_sq + x0;
                        y = 2 * x * y + y0;
                        x = temp;
                        ++iter;
                    }

                    // If the point is in the set (or approximately close to it), color
                    // the pixel black.
                    if (iter == MaxIterations)
                    {
                        *(int *)destPixel = 0;
                    }
                    // Otherwise, select a color that is based on the current iteration.
                    else
                    {
                        var red = (byte)((iter % 64) * 4);
                        *(int*)destPixel = red << 16;
                    }

                    // Move to the next point.
                    destPixel += 4;
                }
            }
        }
    }
}
