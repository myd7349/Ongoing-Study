[w64devkit](https://github.com/skeeto/w64devkit)

Toast Notification

- [ToastNotifications](https://github.com/rafallopatka/ToastNotifications)

- [TwitchNotify/WindowsToast.h at master · mmozeiko/TwitchNotify · GitHub](https://github.com/mmozeiko/TwitchNotify/blob/master/WindowsToast.h)

- [WinToast](https://github.com/mohabouje/WinToast)

Printing

- https://github.com/zufuliu/notepad2/blob/main/src/Bridge.cpp

- [Line width scale](https://github.com/gnuplot/gnuplot/blob/86ba381e842981723e210ddfb50923e4f403392a/src/win/wgdiplus.cpp#L539-L549)

  ```cpp
	/* Need to scale line widths for raster printers so they are the same
	   as on screen */
	if (target == DRAW_PRINTER) {
		HDC hdc = graphics.GetHDC();
		HDC hdc_screen = GetDC(NULL);
		lw_scale = (double) GetDeviceCaps(hdc, LOGPIXELSX) /
		           (double) GetDeviceCaps(hdc_screen, LOGPIXELSY);
		line_width *= lw_scale;
		ReleaseDC(NULL, hdc_screen);
		graphics.ReleaseHDC(hdc);
	}
  ```

- https://github.com/oxyplot/oxyplot/blob/205e968870c292ecaeab2cb9e7f34904897126cb/Source/OxyPlot.SkiaSharp/PdfExporter.cs#L59-L69
  ```csharp
  public void Export(IPlotModel model, Stream stream)
  {
      using var document = SKDocument.CreatePdf(stream);
      using var pdfCanvas = document.BeginPage(this.Width, this.Height);
      using var context = new SkiaRenderContext { RenderTarget = RenderTarget.VectorGraphic, SkCanvas = pdfCanvas, UseTextShaping = this.UseTextShaping };
      const float dpiScale = 72f / 96;
      context.DpiScale = dpiScale;
      model.Update(true);
      pdfCanvas.Clear(model.Background.ToSKColor());
      model.Render(context, new OxyRect(0, 0, this.Width / dpiScale, this.Height / dpiScale));
  }
  ```

- [Q193943: HOWTO: Use GetDeviceCaps to Determine Margins on a Page | KnowledgeBase Archive](https://jeffpar.github.io/kbarchive/kb/193/Q193943/)
  
  > ```
  >         Private Const HORZRES = 8
  >         Private Const VERTRES = 10
  >         Private Const LOGPIXELSX = 88
  >         Private Const LOGPIXELSY = 90
  >         Private Const PHYSICALWIDTH = 110
  >         Private Const PHYSICALHEIGHT = 111
  >         Private Const PHYSICALOFFSETX = 112
  >         Private Const PHYSICALOFFSETY = 113
  > ```
  
  For example:
  
  - Microsoft Print to PDF
    
    ```
    GetDeviceCaps(HORZSIZE) == 297
    GetDeviceCaps(VERTSIZE) == 210
    GetDeviceCaps(HORZRES) == 7016
    GetDeviceCaps(VERTRES) == 4961
    GetDeviceCaps(LOGPIXELSX) == 600
    GetDeviceCaps(LOGPIXELSY) == 600
    GetDeviceCaps(PHYSICALWIDTH) == 7016
    GetDeviceCaps(PHYSICALHEIGHT) == 4961
    GetDeviceCaps(PHYSICALOFFSETX) == 0
    GetDeviceCaps(PHYSICALOFFSETY) == 0
    ```
  
  - HP LaserJet 400 M401 PCL 6, a real printer
    
    ```
    GetDeviceCaps(HORZSIZE) == 289
    GetDeviceCaps(VERTSIZE) == 202
    GetDeviceCaps(HORZRES) == 6815
    GetDeviceCaps(VERTRES) == 4760
    GetDeviceCaps(LOGPIXELSX) == 600
    GetDeviceCaps(LOGPIXELSY) == 600
    GetDeviceCaps(PHYSICALWIDTH) == 7015
    GetDeviceCaps(PHYSICALHEIGHT) == 4960
    GetDeviceCaps(PHYSICALOFFSETX) == 100
    GetDeviceCaps(PHYSICALOFFSETY) == 100
    ```
  
  Both of the printers above have a 600 DPI resolution.
  
  > 7016 ÷ 600 × 2.54 = 29.701cm
  > 
  > 4961 ÷ 600 × 2.54 = 21.0cm
  > 
  > 6815  ÷  600  ×  2.54 = 28.8501cm
  > 
  > 4760  ÷  600  ×  2.54 = 20.15cm
  > 
  > 100 ÷ 600 × 2.54 = 0.423333cm

- [Printing does not start at the top edge of the page](https://stackoverflow.com/questions/21448977/printing-does-not-start-at-the-top-edge-of-the-page)

ImageBase

- C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29333\crt\src\vcruntime\exe_common.inl
  
  > ```cpp
  > #elif defined _SCRT_STARTUP_WINMAIN
  > 
  >     using main_policy = __scrt_winmain_policy;
  >     using file_policy = __scrt_file_policy;
  >     using argv_policy = __scrt_narrow_argv_policy;
  >     using environment_policy = __scrt_narrow_environment_policy;
  > 
  >     static int __cdecl invoke_main()
  >     {
  >         return WinMain(
  >             reinterpret_cast<HINSTANCE>(&__ImageBase),
  >             nullptr,
  >             _get_narrow_winmain_command_line(),
  >             __scrt_get_show_window_mode());
  >     }
  > 
  > #elif defined _SCRT_STARTUP_WWINMAIN
  > ```

AttachConsole used in [PyStand/PyStand.cpp at 654066cd6162787cf5d72d3f4274f5aea5dc14d8 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/blob/654066cd6162787cf5d72d3f4274f5aea5dc14d8/PyStand.cpp#L345)

- [Using AttachConsole, user must hit enter to get regular command line](https://stackoverflow.com/questions/1305257/using-attachconsole-user-must-hit-enter-to-get-regular-command-line)

- [c# - Can one executable be both a console and GUI application? - Stack Overflow](https://stackoverflow.com/questions/493536/can-one-executable-be-both-a-console-and-gui-application/494000#494000)

- [A C++ Debug Stream for Win32](https://marknelson.us/posts/2001/09/01/win32-debug-stream.html)

[mctrl](https://github.com/mity/mctrl)

- [OpenHashTab](https://github.com/namazso/OpenHashTab)

[SQLyog Community Edition](https://github.com/webyog/sqlyog-community)

[GitHub - d0vgan/nppexec: NppExec (plugin for Notepad++)](https://github.com/d0vgan/nppexec)

[nppPluginManager](https://github.com/bruderstein/nppPluginManager)

MAX_PATH

- [Maximum Path Length Limitation - Win32 apps | Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=cmd)

- [Enable or Disable Win32 Long Paths in Windows 10 | Tutorials](https://www.tenforums.com/tutorials/51704-enable-disable-win32-long-paths-windows-10-a.html)

I wrote a DLL in C++ and it exports some C interfaces. Besides, it exports two symbols like this:

```
public: __thiscall std::_Mutex::_Mutex(enum std::_Uninitialized)
public: class std::_Init_locks & __thiscall std::_Init_locks::operator=(class std::_Init_locks const &)
```

[STL/xlock.cpp at main · microsoft/STL · GitHub](https://github.com/microsoft/STL/blob/main/stl/src/xlock.cpp)

[MouseButtonClicker](https://github.com/DavidAnson/MouseButtonClicker)

[embed window(glfwCreateWindow) as child to C++ MFC parent form](https://stackoverflow.com/questions/46152212/embed-windowglfwcreatewindow-as-child-to-c-mfc-parent-form)

[MFC: Fix a console on a GUI](https://stackoverflow.com/questions/9567253/mfc-fix-a-console-on-a-gui)

[MFC: Display output of a process asynchronously(concurrently) while process is in execution in a win32 text area (mfc application)](https://stackoverflow.com/questions/9480030/mfc-display-output-of-a-process-asynchronouslyconcurrently-while-process-is-i)

[embed cmd in win32 application and text not selectable](https://stackoverflow.com/questions/50043663/embed-cmd-in-win32-application-and-text-not-selectable)

https://github.com/MediaArea/ZenLib

[dependency](https://github.com/JelinYao/dependency)

https://github.com/JelinYao/AsyncIPC
