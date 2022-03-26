##### WriteableBitmap

- [WPF - Rendering "Real Time" Best Practice](https://stackoverflow.com/questions/23854176/wpf-rendering-real-time-best-practice)

- [WPF charting/visualization of realtime data](https://stackoverflow.com/questions/2517318/wpf-charting-visualization-of-realtime-data)

  > The **retained** mode rendering engine in WPF / Silverlight delivers poor performance for this type of work. I've worked on a number of systems that were upgraded from Windows Forms to WPF where the client was sorely dissapointed by the rendering performance of this "GPU Accelerated" framework!

- [Possible to InvalidateVisual() on a given region instead of entire WPF control?](https://stackoverflow.com/questions/2576599/possible-to-invalidatevisual-on-a-given-region-instead-of-entire-wpf-control)

  > WPF is a **retained** drawing system. That means OnRender() might better be called AccumulateDrawingObjects(). It's actually accumulating a tree of live drawing objects, which only needs to happen once per layout. It then uses these objects to draw your UI whenever it needs to. To change how a portion of your UI looks without re-layout, some objects (like DrawingGroup, RenderTargetBitmap, and WriteableBitmap) can be updated after OnRender(), anytime you like.

- https://en.wikipedia.org/wiki/Retained_mode

- [wpf writeablebitmap: how to set the pixel width and height](https://stackoverflow.com/questions/17345225/wpf-writeablebitmap-how-to-set-the-pixel-width-and-height)
- [WriteableBitmap](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.writeablebitmap?view=windowsdesktop-6.0)
- [WPF/WinForms/GDI interop: converting a WriteableBitmap to a System.Drawing.Image?](https://stackoverflow.com/questions/3239449/wpf-winforms-gdi-interop-converting-a-writeablebitmap-to-a-system-drawing-image)
- SkiaSharp

  - [SKElement Class](https://docs.microsoft.com/en-us/dotnet/api/skiasharp.views.wpf.skelement?view=skiasharp-views-2.88)

  - [Maui.Graphics WPF Quickstart](https://swharden.com/csdv/maui.graphics/quickstart-wpf/)

  - [WPFExtensions.ToWriteableBitmap](https://docs.microsoft.com/en-us/dotnet/api/skiasharp.views.wpf.wpfextensions.towriteablebitmap?view=skiasharp-views-2.88)
    - https://github.com/mono/SkiaSharp/blob/main/source/SkiaSharp.Views/SkiaSharp.Views.WPF/WPFExtensions.cs
  - https://github.com/unoplatform/uno/issues/4059
  - [WPF 使用 Skia 绘制 WriteableBitmap 图片](https://blog.lindexi.com/post/WPF-%E4%BD%BF%E7%94%A8-Skia-%E7%BB%98%E5%88%B6-WriteableBitmap-%E5%9B%BE%E7%89%87.html)
  - [WPF 自己封装 Skia 差量绘制控件](https://blog.lindexi.com/post/WPF-%E8%87%AA%E5%B7%B1%E5%B0%81%E8%A3%85-Skia-%E5%B7%AE%E9%87%8F%E7%BB%98%E5%88%B6%E6%8E%A7%E4%BB%B6.html)
- [WPF 使用不安全代码快速从数组转 WriteableBitmap](https://blog.lindexi.com/post/WPF-%E4%BD%BF%E7%94%A8%E4%B8%8D%E5%AE%89%E5%85%A8%E4%BB%A3%E7%A0%81%E5%BF%AB%E9%80%9F%E4%BB%8E%E6%95%B0%E7%BB%84%E8%BD%AC-WriteableBitmap.html)
- [Resizing WritableBitmap](https://stackoverflow.com/questions/3300986/resizing-writablebitmap)
- Cairo
  - [how to fast redrawing an image buffer](https://stackoverflow.com/questions/15773965/how-to-fast-redrawing-an-image-buffer)

- [Workaround for memory leak when using WriteableBitmap.AddDirtyRect()](https://stackoverflow.com/questions/24960650/workaround-for-memory-leak-when-using-writeablebitmap-adddirtyrect)

- [FFmpegMediaPlayer](https://github.com/fallingrust/FFmpegMediaPlayer)

- GDI+

  - [WriteableBitmapInWPF](https://github.com/IvanWhisper/WriteableBitmapInWPF)

- DPI issue
  - [Wpf Dpi and pixel-perfect WritableBitmap](https://stackoverflow.com/questions/28562954/wpf-dpi-and-pixel-perfect-writablebitmap)
  - [Screen Resolution Problem In WPF?](https://stackoverflow.com/questions/2236173/screen-resolution-problem-in-wpf)
  - [How can I get the DPI in WPF?](https://stackoverflow.com/questions/1918877/how-can-i-get-the-dpi-in-wpf)
  - [How can I get the correct DPI of my screen in WPF?](https://stackoverflow.com/questions/54659859/how-can-i-get-the-correct-dpi-of-my-screen-in-wpf)
  - [How can I get images in XAML to display as their actual size?](https://stackoverflow.com/questions/1841511/how-can-i-get-images-in-xaml-to-display-as-their-actual-size)
  - [WPF: How to display an image at its original size?](https://stackoverflow.com/questions/3055550/wpf-how-to-display-an-image-at-its-original-size)
  - [Blurry Bitmaps](https://docs.microsoft.com/en-us/archive/blogs/dwayneneed/blurry-bitmaps)
