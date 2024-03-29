1. [Center text output from Graphics.DrawString()](https://stackoverflow.com/questions/7991/center-text-output-from-graphics-drawstring)
   
   > ```cs
   >     private void DrawLetter()
   >     {
   >         Graphics g = this.CreateGraphics();
   > 
   >         float width = ((float)this.ClientRectangle.Width);
   >         float height = ((float)this.ClientRectangle.Width);
   > 
   >         float emSize = height;
   > 
   >         Font font = new Font(FontFamily.GenericSansSerif, emSize, FontStyle.Regular);
   > 
   >         font = FindBestFitFont(g, letter.ToString(), font, this.ClientRectangle.Size);
   > 
   >         SizeF size = g.MeasureString(letter.ToString(), font);
   >         g.DrawString(letter, font, new SolidBrush(Color.Black), (width-size.Width)/2, 0);
   > 
   >     }
   > 
   >     private Font FindBestFitFont(Graphics g, String text, Font font, Size proposedSize)
   >     {
   >         // Compute actual size, shrink if needed
   >         while (true)
   >         {
   >             SizeF size = g.MeasureString(text, font);
   > 
   >             // It fits, back out
   >             if (size.Height <= proposedSize.Height &&
   >                  size.Width <= proposedSize.Width) { return font; }
   > 
   >             // Try a smaller font (90% of old size)
   >             Font oldFont = font;
   >             font = new Font(font.Name, (float)(font.Size * .9), font.Style);
   >             oldFont.Dispose();
   >         }
   >     }
   > ```

2. Double Buffered Graphics
   
   - [Double Buffered Graphics](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/double-buffered-graphics?view=netframeworkdesktop-4.8)
   - https://github.com/dotnet/runtime/blob/main/src/libraries/System.Drawing.Common/src/System/Drawing/BufferedGraphics.Windows.cs

3. https://docs.microsoft.com/en-us/dotnet/api/system.drawing?view=net-6.0
   
   > Some types in the `System.Drawing` namespace rely on [GDI+](https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-gdi-start), which is not supported in Windows services and ASP.NET Core and ASP.NET apps. These types are in the [System.Drawing.Common](https://www.nuget.org/packages/System.Drawing.Common/) NuGet package and include [System.Drawing.Bitmap](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.bitmap?view=net-6.0) and [System.Drawing.Font](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.font?view=net-6.0). However, primitive types in the namespace, such as [System.Drawing.Color](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.color?view=net-6.0), [System.Drawing.Size](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.size?view=net-6.0), [System.Drawing.Point](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.point?view=net-6.0), and [System.Drawing.Rectangle](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.rectangle?view=net-6.0), can be used in any application.
   
   > If you can't use `System.Drawing` with your application, recommended alternatives include [ImageSharp](https://github.com/SixLabors/ImageSharp), [SkiaSharp](https://github.com/mono/SkiaSharp), [Windows Imaging Components](https://docs.microsoft.com/en-us/windows/desktop/wic/-wic-about-windows-imaging-codec), and [Microsoft.Maui.Graphics](https://github.com/dotnet/Microsoft.Maui.Graphics).

4. [Breaking change: System.Drawing.Common only supported on Windows - .NET | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/core/compatibility/core-libraries/6.0/system-drawing-common-windows-only)

5. [How do I install System.Drawing.Common in a project that uses '.NETFramework,Version=v4.5.2'?](https://stackoverflow.com/questions/54984173/how-do-i-install-system-drawing-common-in-a-project-that-uses-netframework-ver)

6. [How to: Print a Windows Form - Windows Forms .NET Framework | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/how-to-print-a-windows-form?view=netframeworkdesktop-4.8)
   
   > ```csharp
   > Size s = this.Size;
   > memoryImage = new Bitmap(s.Width, s.Height, myGraphics);
   > Graphics memoryGraphics = Graphics.FromImage(memoryImage);
   > memoryGraphics.CopyFromScreen(this.Location.X, this.Location.Y, 0, 0, s);
   > ```

7. [C# Painting a form into a MetaFile graphics object](https://stackoverflow.com/questions/49146656/c-sharp-painting-a-form-into-a-metafile-graphics-object)
   
   > ```csharp
   > Graphics g = Graphics.FromImage(new Bitmap(this.Width, this.Height));
   > IntPtr hdc = g.GetHdc();
   > 
   > Metafile imageMetafile = new Metafile(filepath, hdc);
   > 
   > using (Graphics imageGraphics = Graphics.FromImage(imageMetafile)) 
   > {
   >        imageGraphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
   >        imageGraphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
   >        this.InvokePaint(this, new PaintEventArgs(imageGraphics, new Rectangle(0, 0, this.Width, this.Height)));
   > }
   > 
   > g.ReleaseHdc();
   > g.Dispose();
   > ```

8. [ScreenCapture.cs](https://github.com/oxyplot/oxyplot/blob/release/v2.1.0/Source/Examples/WPF/WpfExamples/ScreenCapture.cs)

   ```csharp
   public static Bitmap Capture(int left, int top, int width, int height)
   {
       var hDesk = NativeMethods.GetDesktopWindow();
       var hSrce = NativeMethods.GetWindowDC(hDesk);
       var hDest = NativeMethods.CreateCompatibleDC(hSrce);
       var hBmp = NativeMethods.CreateCompatibleBitmap(hSrce, width, height);
       var hOldBmp = NativeMethods.SelectObject(hDest, hBmp);
       NativeMethods.BitBlt(hDest, 0, 0, width, height, hSrce, left, top, CopyPixelOperation.SourceCopy | CopyPixelOperation.CaptureBlt);
       var bmp = Image.FromHbitmap(hBmp);
       NativeMethods.SelectObject(hDest, hOldBmp);
       NativeMethods.DeleteObject(hBmp);
       NativeMethods.DeleteDC(hDest);
       NativeMethods.ReleaseDC(hDesk, hSrce);
       return bmp;
   }
   ```
