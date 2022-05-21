Projects using MFC:

- [BowPad](https://github.com/stefankueng/BowPad)

- [EMFexplorer](http://frazmitic.free.fr/emfexplorer/)

- [ExifPro](https://github.com/mikekov/ExifPro)
  
  - [Shutter-cn](https://github.com/dream7180/Shutter-cn)

- [MPC-HC](https://github.com/mpc-hc/mpc-hc)

- [TortoiseGit](https://github.com/TortoiseGit/TortoiseGit)

- [TrafficMonitor](https://github.com/zhongyang219/TrafficMonitor)

- [WinMerge](https://github.com/WinMerge/winmerge)

- [Wumpbin](https://www.benf.org/other/wumpbin/index.html)

Q&A:

- [How to get the command line arguments in MFC applications?](https://stackoverflow.com/questions/5562877/how-to-get-the-command-line-arguments-in-mfc-applications)

ROI:

- [CDrawingManager](https://docs.microsoft.com/en-us/cpp/mfc/reference/cdrawingmanager-class?view=msvc-170)

Font:

- [Use system native default font in GUI](https://github.com/ventoy/Ventoy/pull/1291)
  - [Using MS Shell Dlg and MS Shell Dlg 2](https://docs.microsoft.com/en-us/windows/win32/intl/using-ms-shell-dlg-and-ms-shell-dlg-2)

[CDC Class | Microsoft Docs](https://docs.microsoft.com/en-us/cpp/mfc/reference/cdc-class?view=msvc-170)

> `CDC` contains two device contexts, [`m_hDC`](https://docs.microsoft.com/en-us/cpp/mfc/reference/cdc-class?view=msvc-170#m_hdc) and [`m_hAttribDC`](https://docs.microsoft.com/en-us/cpp/mfc/reference/cdc-class?view=msvc-170#m_hattribdc), which, on creation of a `CDC` object, refer to the same device. `CDC` directs all output GDI calls to `m_hDC` and most attribute GDI calls to `m_hAttribDC`. (An example of an attribute call is `GetTextColor`, while `SetTextColor` is an output call.)
> 
> For example, the framework uses these two device contexts to implement a `CMetaFileDC` object that will send output to a metafile while reading attributes 
> from a physical device. Print preview is implemented in the framework in
>  a similar fashion. You can also use the two device contexts in a 
> similar way in your application-specific code.

[Display Device Contexts - Win32 apps | Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/gdi/display-device-contexts)

> *Private device contexts* are display DCs that, unlike common 
> device contexts, retain any changes to the default data even after an 
> application releases them. Private device contexts are used in 
> applications that perform numerous drawing operations such as 
> computer-aided design (CAD) applications, desktop-publishing 
> applications, drawing and painting applications, and so on. Private 
> device contexts are not part of the system cache and therefore need not 
> be released after use. The system automatically removes a private device
>  context after the last window of that class has been destroyed.
> 
> An application creates a private device context by first specifying the CS_OWNDC window-class style when it initializes the **style** member of the [**WNDCLASS**](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa) structure and calls the [**RegisterClass**](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa) function. (For more information about window classes, see [Window Classes](https://docs.microsoft.com/en-us/windows/win32/winmsg/window-classes).)
> 
> After creating a window with the CS_OWNDC style, an application can call the [**GetDC**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-getdc), [**GetDCEx**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-getdcex), or [**BeginPaint**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-beginpaint) function once to obtain a handle identifying a private device context. 
> The application can continue using this handle (and the associated DC) 
> until it deletes the window created with this class. Any changes to 
> graphic objects and their attributes, or graphic modes are retained by 
> the system until the window is deleted.

[How to create a resizable CDialog in MFC?](https://stackoverflow.com/questions/138040/how-to-create-a-resizable-cdialog-in-mfc)

[MFC Dynamic Dialog Layout](https://devblogs.microsoft.com/cppblog/mfc-dynamic-dialog-layout/)

[ResizableLib](https://www.codeproject.com/Articles/1175/ResizableLib) - [GitHub](https://github.com/ppescher/resizablelib) - [TortoiseGit is using this lib.](https://github.com/TortoiseGit/TortoiseGit/tree/master/ext/ResizableLib)

[Where can I see ATLTRACE output?](https://stackoverflow.com/questions/47585567/where-can-i-see-atltrace-output)
