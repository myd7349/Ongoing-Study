##### CompositionTarget.Rendering

- https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.compositiontarget.rendering?view=windowsdesktop-6.0

- https://docs.microsoft.com/en-us/dotnet/desktop/wpf/graphics-multimedia/how-to-render-on-a-per-frame-interval-using-compositiontarget?view=netframeworkdesktop-4.8

- [Why is Frame Rate in WPF Irregular and Not Limited To Monitor Refresh?](https://stackoverflow.com/questions/5812384/why-is-frame-rate-in-wpf-irregular-and-not-limited-to-monitor-refresh)
  > Because of this, the CompositionTarget.Rendering event can be raised multiple times per “frame”. We report the intended “frame time” in the RenderingEventArgs, and applications should only do “per-frame” work when the reported frame time changes.

  ```csharp
  public static class CompositionTargetEx
  {
      private static TimeSpan _last = TimeSpan.Zero;
      private static event EventHandler<RenderingEventArgs> _FrameUpdating;
  
      public static event EventHandler<RenderingEventArgs> Rendering
      {
          add
          {
              if (_FrameUpdating == null)
                  CompositionTarget.Rendering += CompositionTarget_Rendering;
              _FrameUpdating += value;
          }
          remove
          {
              _FrameUpdating -= value;
              if (_FrameUpdating == null)
                  CompositionTarget.Rendering -= CompositionTarget_Rendering;
          }
      }
  
      static void CompositionTarget_Rendering(object sender, EventArgs e)
      {
          RenderingEventArgs args = (RenderingEventArgs)e;
          if (args.RenderingTime == _last)
              return;
  
          _last = args.RenderingTime;
          _FrameUpdating(sender, args);
      }
  }
  ```

  So in https://github.com/reneschulte/WriteableBitmapEx/blob/master/Source/WriteableBitmapExBlitSample.Wpf/MainWindow.xaml.cs, the FPS is very strange.

- https://github.com/reneschulte/WriteableBitmapEx/blob/master/Source/WriteableBitmapExBlitSample.Wpf/MainWindow.xaml.cs

- https://github.com/walterlv/walterlv.demo/blob/master/Walterlv.Demo.HighPerformanceBitmap/Walterlv.Demo.HighPerformanceBitmap/MainWindow.xaml.cs
