using System;

using SkiaSharp;

namespace ECGDemo
{
    public static class ECGrid
    {
        public static void DrawDotted(
            SKCanvas canvas, int width, int height,
            SKColor backColor, SKColor grid5mmColor, SKColor grid1mmColor,
            int dotsPerMm)
        {
            if (canvas == null)
                throw new ArgumentNullException(nameof(canvas));

            canvas.Clear(backColor);

            var dotsPer5mm = dotsPerMm * 5;

            using (var paint = new SKPaint())
            {
                paint.IsStroke = true;
                paint.PathEffect = SKPathEffect.CreateDash(new float[] { 1, 1 }, 1);
                paint.Color = grid5mmColor;

                // 5mm, horz
                for (int y = 0; y < height; y += dotsPer5mm)
                    canvas.DrawLine(0, y, width, y, paint);

                // 5mm, vert
                for (int x = 0; x < width; x += dotsPer5mm)
                    canvas.DrawLine(x, 0, x, height, paint);

                paint.Color = grid1mmColor;
                //paint.BlendMode = SKBlendMode.Src;
                paint.IsStroke = false;
                paint.PathEffect.Dispose();
                paint.PathEffect = null;

                // 1mm
                for (int y = 0; y < height; y += dotsPerMm)
                {
                    if (y % dotsPer5mm == 0)
                        continue;

                    for (int x = 0; x < width; x += dotsPerMm)
                    {
                        if (x % dotsPer5mm == 0)
                            continue;

#if true
                        canvas.DrawPoint(x, y, paint);
#else
                        /*
		                public void DrawPoint (float x, float y, SKColor color)
		                {
			                using (var paint = new SKPaint { Color = color, BlendMode = SKBlendMode.Src }) {
				                DrawPoint (x, y, paint);
			                }
		                }
                        */
                        canvas.DrawPoint(x, y, grid1mmColor);
#endif
                    }
                }
            }

            // Exit
        }
    }
}


// References:
// [Dots and Dashes in SkiaSharp](https://docs.microsoft.com/en-us/xamarin/xamarin-forms/user-interface/graphics/skiasharp/paths/dots)
