using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ECGDemo
{
    public static class ECGrid
    {
        public static void DrawDotted(WriteableBitmap bitmap,
            Color backColor, Color grid5mmColor, Color grid1mmColor,
            int dotsPerMm)
        {
            if (bitmap == null)
                throw new ArgumentNullException(nameof(bitmap));

            bitmap.Clear(backColor);

            var dotsPer5mm = dotsPerMm * 5;

            // 5mm, horz
            for (int y = 0; y < bitmap.PixelHeight; y += dotsPer5mm)
                bitmap.DrawLineDotted(0, y, bitmap.PixelWidth, y, 1, 1, grid5mmColor);

            // 5mm, vert
            for (int x = 0; x < bitmap.PixelWidth; x += dotsPer5mm)
                bitmap.DrawLineDotted(x, 0, x, bitmap.PixelHeight, 1, 1, grid5mmColor);

            // 1mm
            for (int y = 0; y < bitmap.PixelHeight; y += dotsPerMm)
            {
                if (y % dotsPer5mm == 0)
                    continue;

                for (int x = 0; x < bitmap.PixelWidth; x += dotsPerMm)
                {
                    if (x % dotsPer5mm == 0)
                        continue;

                    bitmap.SetPixel(x, y, grid1mmColor);
                }
            }
        }
    }
}
