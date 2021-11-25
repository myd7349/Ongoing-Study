[c# - &quot;Parameter Not Valid&quot; on call to GetHenhmetafile(), trying to save an in-memory Graphics object as EMF - Stack Overflow](https://stackoverflow.com/questions/20390268/parameter-not-valid-on-call-to-gethenhmetafile-trying-to-save-an-in-memory)

[Working with Metafile Images in .NET - CodeProject](https://www.codeproject.com/Articles/177394/Working-with-Metafile-Images-in-NET)

[Does GetHenhmetafile cause the Metafile to be permanently invalid, or just until DeleteEnhMetaFile, or not at all?](https://social.msdn.microsoft.com/Forums/windows/en-US/b0940c7f-3123-446e-b613-376d6afeecec/does-gethenhmetafile-cause-the-metafile-to-be-permanently-invalid-or-just-until-deleteenhmetafile?forum=winforms)

> GetHenhmetafile to get a GDI handle to an EMF, and the subsequent 
> DeleteEnhMetaFile to delete that handle, must be used in pairs.

[Copy Enhanced Metafile from clipboard and save it as an image](https://stackoverflow.com/questions/18602171/copy-enhanced-metafile-from-clipboard-and-save-it-as-an-image)

[Make and use a metafile in C# - C# HelperC# Helper](http://csharphelper.com/blog/2016/04/make-use-metafile-c/)

> A metafile is a drawing that doesn’t just contain the pixels in an 
> image. Instead it contains a record of the commands used to produce a 
> drawing so you can rerun those commands later.

> ```csharp
> // Return a metafile with the indicated size.
> private Metafile MakeMetafile(float width, float height,
>     string filename)
> {
>     // Make a reference bitmap.
>     using (Bitmap bm = new Bitmap(16, 16))
>     {
>         using (Graphics gr = Graphics.FromImage(bm))
>         {
>             RectangleF bounds =
>                 new RectangleF(0, 0, width, height);
> 
>             Metafile mf;
>             if ((filename != null) && (filename.Length > 0))
>                 mf = new Metafile(filename, gr.GetHdc(),
>                     bounds, MetafileFrameUnit.Pixel);
>             else
>                 mf = new Metafile(gr.GetHdc(), bounds,
>                     MetafileFrameUnit.Pixel);
> 
>             gr.ReleaseHdc();
>             return mf;
>         }
>     }
> }
> ```
> 
> To create a new metafile, you need a graphics device handle. To get one,
>  the code create a 16×16 pixel bitmap. The bitmap’s size isn’t 
> important; the code really just needs to use it to get a graphics device
>  handle.
> 
> ```csharp
> // Draw on the metafile.
> private void DrawOnMetafile(Metafile mf)
> {
>     using (Graphics gr = Graphics.FromImage(mf))
>     {
>         gr.SmoothingMode = SmoothingMode.AntiAlias;
>         using (Pen pen = new Pen(Color.Red, 5))
>         {
>             gr.DrawEllipse(pen, 5, 5, 90, 90);
>         }
>         using (Brush brush = new SolidBrush(
>             Color.FromArgb(255, 128, 255, 128)))
>         {
>             gr.FillEllipse(brush, 5, 25, 90, 50);
>         }
>         using (Brush brush = new SolidBrush(
>             Color.FromArgb(128, 128, 128, 255)))
>         {
>             gr.FillEllipse(brush, 25, 5, 50, 90);
>         }
>         Point[] points =
>         {
>             new Point(50, 5),
>             new Point(94, 50),
>             new Point(50, 94),
>             new Point(5, 50),
>         };
>         gr.DrawPolygon(Pens.Blue, points);
>     }
> }
> ```
> 
> ```csharp
> // Draw the metafile onto a bitmap.
> private Bitmap MetafileToBitmap(Metafile mf)
> {
>     Bitmap bm = new Bitmap(mf.Width, mf.Height);
>     using (Graphics gr = Graphics.FromImage(bm))
>     {
>         GraphicsUnit unit = GraphicsUnit.Pixel;
>         RectangleF source = mf.GetBounds(ref unit);
> 
>         PointF[] dest =
>         {
>             new PointF(0, 0),
>             new PointF(source.Width, 0),
>             new PointF(0, source.Height),
>         };
>         gr.DrawImage(mf, dest, source, GraphicsUnit.Pixel);
>     }
>     return bm;
> }
> ```

[MetafileFrameUnit Enum (System.Drawing.Imaging) | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.imaging.metafileframeunit?view=dotnet-plat-ext-6.0)

> | GdiCompatible | 7   | The unit of measurement is 0.01 millimeter. Provided for compatibility with GDI. |
> | ------------- | --- | -------------------------------------------------------------------------------- |

[Different scaling when drawing Metafile on different machines](https://stackoverflow.com/questions/26834715/different-scaling-when-drawing-metafile-on-different-machines)

> ```csharp
> private void MainForm_Paint(object sender, PaintEventArgs e)
> {
>    var g = e.Graphics;
>    var blueBrush = new SolidBrush(Color.Blue);
>    var bluePen = new Pen(blueBrush);
>    g.DrawRectangle(bluePen, 0, 0, 200, 200);
>    g.DrawLine(bluePen, 100, 0, 100, 200);
>    g.DrawLine(bluePen, 0, 100, 200, 100);
>    g.DrawString(g.DpiX+" dpi", new Font("Arial", 10), blueBrush, 0, 205);
> 
>    Metafile metafile;
>    var size = new Size(200, 200);
>    using (var stream = new MemoryStream())
>    {
>       using (Graphics offScreenBufferGraphics = Graphics.FromHwndInternal(IntPtr.Zero))
>       {
>          IntPtr deviceContextHandle = offScreenBufferGraphics.GetHdc();
>          metafile = new Metafile(stream, deviceContextHandle, new RectangleF(0, 0, size.Width, size.Height), MetafileFrameUnit.Millimeter, EmfType.EmfPlusOnly);
>          offScreenBufferGraphics.ReleaseHdc();
> 
>          using (Graphics mg = Graphics.FromImage(metafile))
>          {
>             mg.PageUnit = GraphicsUnit.Millimeter;
> 
>             var redPen = new Pen(new SolidBrush(Color.Red));
>             const float scaleFactor = 0.75f;
>             mg.ScaleTransform(scaleFactor, scaleFactor);
>             mg.DrawLine(redPen, 0, 0, 200, 200);
>             mg.DrawLine(redPen, 0, 200, 200, 0);
>          }
>       }
>    }
> 
>    g.DrawImage(metafile, 0, 0, 200, 200);
> }
> ```
> 
> Found the answer myself after reading [this](http://www.codeproject.com/Articles/177394/Working-with-Metafile-Images-in-Net) code project article. Turns out that the screen size on the machine 
> (1920x1200 on desktop and 1600x900 on laptop) affect the resolution of 
> the metafile. The assumption of 72dpi that was used to calculate the 
> scale factor 0.75 was somewhat correct on my desktop machine, but not on
>  the Win8 laptop.
> 
> The metafile resolution can be fetched from the metafile header, and then used to calculate the correct scaling factor:
> 
> ```csharp
> var metafileHeader = metafile.GetMetafileHeader();
> float sx = metafileHeader.DpiX/g.DpiX;
> float sy = metafileHeader.DpiY/g.DpiY;
> mg.ScaleTransform(sx, sy);
> ```
> 
> *The complete code can be found [here](http://pastebin.com/PViFai6X).
> 
> ```csharp
> public partial class MainForm : Form
> {
>     public MainForm()
>     {
>         InitializeComponent();
>     }
> 
>     private void MainForm_Paint(object sender, PaintEventArgs e)
>     {
>         var g = e.Graphics;
>         var blueBrush = new SolidBrush(Color.Blue);
>         var bluePen = new Pen(blueBrush);
>         g.DrawRectangle(bluePen, 0, 0, 200, 200);
>         g.DrawLine(bluePen, 100, 0, 100, 200);
>         g.DrawLine(bluePen, 0, 100, 200, 100);
>         g.DrawString(g.DpiX+" dpi", new Font("Arial", 10), blueBrush, 0, 205);
> 
>         Metafile metafile;
>         MetafileHeader metafileHeader;
>         var size = new Size(200, 200);
>         using (var stream = new MemoryStream())
>         {
>             using (Graphics offScreenBufferGraphics = Graphics.FromHwndInternal(IntPtr.Zero))
>             {
>                 IntPtr deviceContextHandle = offScreenBufferGraphics.GetHdc();
>                 metafile = new Metafile(stream, deviceContextHandle, new RectangleF(0, 0, size.Width, size.Height), MetafileFrameUnit.Millimeter, EmfType.EmfPlusOnly);
>                 offScreenBufferGraphics.ReleaseHdc();
> 
>                 using (Graphics mg = Graphics.FromImage(metafile))
>                 {
>                     mg.PageUnit = GraphicsUnit.Millimeter;
>                     var redPen = new Pen(new SolidBrush(Color.Red));
> 
>                     // This is how to get the correct scale factor:
>                     metafileHeader = metafile.GetMetafileHeader();
>                     float sx = metafileHeader.DpiX/g.DpiX;
>                     float sy = metafileHeader.DpiY/g.DpiY;
>                     mg.ScaleTransform(sx, sy);
> 
>                     mg.DrawLine(redPen, 0, 0, 200, 200);
>                     mg.DrawLine(redPen, 0, 200, 200, 0);
>                 }
>             }
>         }
> 
>         g.DrawImage(metafile, 0, 0, 200, 200);
>         g.DrawString("metafile.Width: " + metafile.Width, new Font("Arial", 10), blueBrush, 0, 220);
>         g.DrawString("metafileHeader.DpiX: " + metafileHeader.DpiX, new Font("Arial", 10), blueBrush, 0, 240);
>     }
> }
> ```
> 
> End.

[EMF image size and resolution differs according to the machine's scaling settings - when created in C#](https://stackoverflow.com/questions/51979439/emf-image-size-and-resolution-differs-according-to-the-machines-scaling-setting)

[Scaling bitmap into EMF via System.Drawing with specific width im millimeters?](https://stackoverflow.com/questions/61380302/scaling-bitmap-into-emf-via-system-drawing-with-specific-width-im-millimeters)

[Windows Display Setting at 150% still shows 96 DPI](https://stackoverflow.com/questions/7003316/windows-display-setting-at-150-still-shows-96-dpi)

> ```csharp
> using (Graphics screen = Graphics.FromHwnd(IntPtr.Zero))
> {
>     IntPtr hdc = screen.GetHdc();
>     int dpiX = GetDeviceCaps(hdc, DeviceCaps.LOGPIXELSX);
>     screen.ReleaseHdc(hdc);
> }
> ```

> ```csharp
> public static int GetSystemDpi()
> {
>     using (Graphics screen = Graphics.FromHwnd(IntPtr.Zero))
>     {
>         IntPtr hdc = screen.GetHdc();
> 
>         int virtualWidth = GetDeviceCaps(hdc, DeviceCaps.HORZRES);
>         int physicalWidth = GetDeviceCaps(hdc, DeviceCaps.DESKTOPHORZRES);
>         screen.ReleaseHdc(hdc);
> 
>         return (int)(96f * physicalWidth / virtualWidth);
>     }
> }
> ```

> ```csharp
> private enum DeviceCaps
> {
>     /// <summary>
>     /// Logical pixels inch in X
>     /// </summary>
>     LOGPIXELSX = 88,
> 
>     /// <summary>
>     /// Horizontal width in pixels
>     /// </summary>
>     HORZRES = 8,
> 
>     /// <summary>
>     /// Horizontal width of entire desktop in pixels
>     /// </summary>
>     DESKTOPHORZRES = 118
> }
> 
> /// <summary>
> /// Retrieves device-specific information for the specified device.
> /// </summary>
> /// <param name="hdc">A handle to the DC.</param>
> /// <param name="nIndex">The item to be returned.</param>
> [DllImport("gdi32.dll")]
> private static extern int GetDeviceCaps(IntPtr hdc, DeviceCaps nIndex);
> ```

[How to make emf file dpi aware](https://stackoverflow.com/questions/54488961/how-to-make-emf-file-dpi-aware)

> First calculate the Display Setting scale factor:
> 
> ```csharp
> // Calculate the scale setting
> // Note: Changing the Display Settings scale changes the screen pixel resolution (HORZRES). 
> // The desktop res is the physical numbers of pixels, and the logical pixel is set at boot up and never changes.
> System.Drawing.Graphics pGFX = System.Drawing.Graphics.FromHwnd(IntPtr.Zero);
> IntPtr hemfDC = pGFX.GetHdc();
> int dtX = GetDeviceCaps(hemfDC, DeviceCap.DESKTOPHORZRES);
> int dtY = GetDeviceCaps(hemfDC, DeviceCap.DESKTOPVERTRES);
> int scX = GetDeviceCaps(hemfDC, DeviceCap.HORZRES);
> int scY = GetDeviceCaps(hemfDC, DeviceCap.VERTRES);
> int lpX = GetDeviceCaps(hemfDC, DeviceCap.LOGPIXELSX);
> int lpY = GetDeviceCaps(hemfDC, DeviceCap.LOGPIXELSY);
> pGFX.ReleaseHdc();
> int dpiX = (int)(((float)dtX / (float)scX) * lpX);
> int dpiY = (int)(((float)dtY / (float)scY) * lpY);
> float scaleX = ((((float)dtX / (float)scX) * lpX) / pGFX.DpiX);
> float scaleY = ((((float)dtY / (float)scY) * lpY) / pGFX.DpiY);
> ```
> 
> Next create the metafile:
> 
> ```csharp
> Metafile image = null;
> MetafileHeader mfh = null;
> SizeF emfSize = new SizeF(pageSize);
> 
> using (MemoryStream stream = new MemoryStream())
> {
>     IntPtr hDC = gfx.GetHdc();
>     try
>     {
>         image = new Metafile(
>             stream,
>             hDC,
>             new RectangleF(new PointF(0, 0), emfSize),
>             MetafileFrameUnit.Inch,
>             EmfType.EmfPlusOnly);
>     }
>     finally
>     {
>         gfx.ReleaseHdc();
>     }
> }
> ```
> 
> Finally, call the drawing code. The drawing code takes a size in pixels,
>  not inches. Note that the size of the file, in pixels, is the size of 
> the user defined scale factor, where 100% is assumed to be g.Dpi (i.e. 
> 96). This assumption has proven to be correct for all the monitors I 
> have tested.
> 
> ```csharp
> if (image != null)
> {
>     using (Graphics g = Graphics.FromImage(image))
>     {
>         mfh = image.GetMetafileHeader();
>         emfSize.Width *= g.DpiX * scaleX;
>         emfSize.Height *= g.DpiY * scaleY;
> 
>         g.PageUnit = GraphicsUnit.Pixel;
>         g.ScaleTransform(mfh.DpiX / g.DpiX, mfh.DpiY / g.DpiY);
> 
>         DrawGraph(g, ref emfSize);
>     }
> }
> ```
> 
> End

[Creating an Enhanced Metafile - Win32 apps | Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/gdi/creating-an-enhanced-metafile)

> ```c
> // Obtain a handle to a reference device context.  
> 
> hdcRef = GetDC(hWnd); 
> 
> // Determine the picture frame dimensions.  
> // iWidthMM is the display width in millimeters.  
> // iHeightMM is the display height in millimeters.  
> // iWidthPels is the display width in pixels.  
> // iHeightPels is the display height in pixels  
> 
> iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE); 
> iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE); 
> iWidthPels = GetDeviceCaps(hdcRef, HORZRES); 
> iHeightPels = GetDeviceCaps(hdcRef, VERTRES); 
> 
> // Retrieve the coordinates of the client  
> // rectangle, in pixels.  
> 
> GetClientRect(hWnd, &rect); 
> 
> // Convert client coordinates to .01-mm units.  
> // Use iWidthMM, iWidthPels, iHeightMM, and  
> // iHeightPels to determine the number of  
> // .01-millimeter units per pixel in the x-  
> //  and y-directions.  
> 
> rect.left = (rect.left * iWidthMM * 100)/iWidthPels; 
> rect.top = (rect.top * iHeightMM * 100)/iHeightPels; 
> rect.right = (rect.right * iWidthMM * 100)/iWidthPels; 
> rect.bottom = (rect.bottom * iHeightMM * 100)/iHeightPels; 
> 
> // Load the filename filter from the string table.  
> 
> LoadString(hInst, IDS_FILTERSTRING, 
>      (LPSTR)szFilter, sizeof(szFilter)); 
> 
> // Replace the '%' separators that are embedded  
> // between the strings in the string-table entry  
> // with '\0'.  
> 
> for (i=0; szFilter[i]!='\0'; i++) 
>     if (szFilter[i] == '%') 
>             szFilter[i] = '\0'; 
> 
> // Load the dialog title string from the table.  
> 
> LoadString(hInst, IDS_TITLESTRING, 
>      (LPSTR)szTitle, sizeof(szTitle)); 
> 
> // Initialize the OPENFILENAME members.  
> 
> szFile[0] = '\0'; 
> 
> Ofn.lStructSize = sizeof(OPENFILENAME); 
> Ofn.hwndOwner = hWnd; 
> Ofn.lpstrFilter = szFilter; 
> Ofn.lpstrFile= szFile; 
> Ofn.nMaxFile = sizeof(szFile)/ sizeof(*szFile); 
> Ofn.lpstrFileTitle = szFileTitle; 
> Ofn.nMaxFileTitle = sizeof(szFileTitle); 
> Ofn.lpstrInitialDir = (LPSTR)NULL; 
> Ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
> Ofn.lpstrTitle = szTitle; 
> 
> // Display the Filename common dialog box. The  
> // filename specified by the user is passed  
> // to the CreateEnhMetaFile function and used to  
> // store the metafile on disk.  
> 
> GetSaveFileName(&Ofn); 
> 
> // Load the description from the string table.  
> 
> LoadString(hInst, IDS_DESCRIPTIONSTRING, 
>      (LPSTR)szDescription, sizeof(szDescription)); 
> 
> // Replace the '%' string separators that are  
> // embedded between strings in the string-table  
> // entry with '\0'.  
> 
> for (i=0; szDescription[i]!='\0'; i++) 
> {
>     if (szDescription[i] == '%') 
>             szDescription[i] = '\0'; 
> }
> 
> // Create the metafile device context.  
> 
> hdcMeta = CreateEnhMetaFile(hdcRef, 
>           (LPTSTR) Ofn.lpstrFile, 
>           &rect, (LPSTR)szDescription); 
> 
> if (!hdcMeta) 
>     errhandler("CreateEnhMetaFile", hWnd); 
> 
> // Release the reference device context.  
> 
> ReleaseDC(hWnd, hdcRef); 
> ```

[Create metafile in C# with specified resolution (dpi)](https://www.c-sharpcorner.com/forums/create-metafile-in-c-sharp-with-specified-resolution-dpi)

> Hello, I'm fairly new to C# .NET and have been working with GDI+ and creating metafiles. I am having one particluar problem however. I am trying to create a metafile that has a certain minimum resolution (specifically, one that has at least 300 dpi for both the x and y axes). I have figured out how to create the metafile using a memory stream, bounding rectangle, and Metafile units like so:
> 
> ```csharp
> PrinterSettings printerSettings = new PrinterSettings();
> Graphics graphics = printerSettings.GetMeasurementGraphics();
> IntPtr ipHdc = graphics.GetHdc();
> Metafile mf = new Metafile(new System.IO.MemoryStream(), ipHdc, new Rectangle(0, 0, 0, 0), MetafileFrameUnit.Document, EmfType.EmfPlusDual);
> graphics.ReleaseHdc(ipHdc);
> graphics.Dispose();
> Graphics grfxMetafile = Graphics.FromImage(mf);
> // .. from here, do drawing, etc....
> ```
> 
> Now I create the metafile just fine and can draw to it, yadda yadda. The problem comes with the Graphics object I use to create the metafile and the drawing. I need the output dpi to be very high (300) because when I send this to the poster printer, i need very high resolution or it looks bad. So I'm stuck trying to get a high dpi device to get a Graphics object with a high dpi. So enter getting the graphics from the PrinterSettings. The problem is, what happens if there is no printer installed (printer settings get graphics call relies on a default printer being installed with a high dpi printer). When I copy/paste this metafile into other documents, I want the metafile to keep the high dpi I created it with. So my question is this: how do you create a high-dpi graphics object to create a metafile in order to have that metafile have a high dpi? Getting a Graphics from a bitmap or other image gives you a dpi that is of screen resolution (96dpi). Does it matter what dpi you use on your graphics object when creating the metafile? I am a bit confused on how to proceed, and google searches turn up mostly empty, or little useful information. **Petzold** uses the PrinterSettings in his book but as I mentioned I can't rely on a high dpi printer being installed. Any ideas? Thanks much in advance...

[System.Drawing.Graphics.DpiX always return 96](https://stackoverflow.com/questions/20057959/system-drawing-graphics-dpix-always-return-96)

> I found solution. My app's manifest has to say it is dpiAware.
> Because I am trying to detect high DPI and show a warning message box 
> and not really trying to make my app dpi aware, I couldn't do that.
> You can get dpi aware information from registry: 
> HKEY_CURRENT_USER\Control Panel\Desktop
> LogPixels.
> 
> If you are using default, you won't have the key. Changing DPI setting will create one.

[Printing high resolution with temporary Bitmap](https://stackoverflow.com/questions/37320586/printing-high-resolution-with-temporary-bitmap)

> It is a good thing that `Graphics.DrawImage` honors the 
> Bitmap's resolution, although it sometimes leads to confusion, when 
> one assumes that all pieces of the puzzle have the same resolution..
> 
> Here you need to set the resolution of the temporary Bitmap explicitly or else if simply inherits the screen resolution..:
> 
> ```csharp
> bmp.SetResolution(600,600)
> ```
> 
> Of course now the Labels' Size will probably not be large enough..
> 
> Also note a problem with terminology: Resolution may mean size i.e. 
> pixels or printer dots but really ought to mean density i.e. `dpi` or ' dots per inch' .
> 
> You want to bring up the size **and** also the `dpi`!

[Create graphics from Metafile error "out of memory"](https://stackoverflow.com/questions/27097700/create-graphics-from-metafile-error-out-of-memory)
