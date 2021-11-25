1. [PrintableArea](https://stackoverflow.com/questions/22400056/print-high-resolution-image-in-c-sharp)
   
   > ```csharp
   > printDialog.PrinterSettings.PrinterName = GetTargetPrinter(); 
   > 
   > int horizontal_dpi = printDialog.PrinterSettings.DefaultPageSettings.PrinterResolution.X;
   > int vertical_dpi = printDialog.PrinterSettings.DefaultPageSettings.PrinterResolution.Y;
   > Decimal final_width_dpi = (((int)printDialog.PrinterSettings.DefaultPageSettings.PrintableArea.Width * horizontal_dpi) / 100); 
   > Decimal final_height_dpi = (((int)printDialog.PrinterSettings.DefaultPageSettings.PrintableArea.Height * vertical_dpi) / 100);
   > 
   > printImage = new Bitmap((int)final_width_dpi, (int)final_height_dpi);
   > 
   > // Set Resolution
   > printImage.SetResolution(horizontal_dpi, vertical_dpi);
   > 
   > Graphics g = System.Drawing.Graphics.FromImage(printImage);
   > ```

2. [How to find the actual printable area? (PrintDocument)](https://stackoverflow.com/questions/8761633/how-to-find-the-actual-printable-area-printdocument)
   
   > ```cs
   > PrintAction printAction = PrintAction.PrintToFile;
   > 
   > private void printDocument_BeginPrint(object sender, PrintEventArgs e)
   > {
   >     // Save our print action so we know if we are printing 
   >     // a preview or a real document.
   >     printAction = e.PrintAction;
   > 
   >     // Set some preferences, our method should print a box with any 
   >     // combination of these properties being true/false.
   >     printDocument.OriginAtMargins = false;   //true = soft margins, false = hard margins
   >     printDocument.DefaultPageSettings.Landscape = false;
   > }
   > 
   > private void printDocument_PrintPage(object sender, PrintPageEventArgs e)
   > {
   >     Graphics g = e.Graphics;
   > 
   >     // If you set printDocumet.OriginAtMargins to 'false' this event 
   >     // will print the largest rectangle your printer is physically 
   >     // capable of. This is often 1/8" - 1/4" from each page edge.
   >     // ----------
   >     // If you set printDocument.OriginAtMargins to 'false' this event
   >     // will print the largest rectangle permitted by the currently 
   >     // configured page margins. By default the page margins are 
   >     // usually 1" from each page edge but can be configured by the end
   >     // user or overridden in your code.
   >     // (ex: printDocument.DefaultPageSettings.Margins)
   > 
   >     // Grab a copy of our "soft margins" (configured printer settings)
   >     // Defaults to 1 inch margins, but could be configured otherwise by 
   >     // the end user. You can also specify some default page margins in 
   >     // your printDocument.DefaultPageSetting properties.
   >     RectangleF marginBounds = e.MarginBounds;
   > 
   >     // Grab a copy of our "hard margins" (printer's capabilities) 
   >     // This varies between printer models. Software printers like 
   >     // CutePDF will have no "physical limitations" and so will return 
   >     // the full page size 850,1100 for a letter page size.
   >     RectangleF printableArea = e.PageSettings.PrintableArea;
   > 
   >     // If we are print to a print preview control, the origin won't have 
   >     // been automatically adjusted for the printer's physical limitations. 
   >     // So let's adjust the origin for preview to reflect the printer's 
   >     // hard margins.
   >     if (printAction == PrintAction.PrintToPreview)
   >         g.TranslateTransform(printableArea.X, printableArea.Y);
   > 
   >     // Are we using soft margins or hard margins? Lets grab the correct 
   >     // width/height from either the soft/hard margin rectangles. The 
   >     // hard margins are usually a little wider than the soft margins.
   >     // ----------
   >     // Note: Margins are automatically applied to the rotated page size 
   >     // when the page is set to landscape, but physical hard margins are 
   >     // not (the printer is not physically rotating any mechanics inside, 
   >     // the paper still travels through the printer the same way. So we 
   >     // rotate in software for landscape)
   >     int availableWidth = (int)Math.Floor(printDocument.OriginAtMargins 
   >         ? marginBounds.Width 
   >         : (e.PageSettings.Landscape 
   >             ? printableArea.Height 
   >             : printableArea.Width));
   >     int availableHeight = (int)Math.Floor(printDocument.OriginAtMargins 
   >         ? marginBounds.Height 
   >         : (e.PageSettings.Landscape 
   >             ? printableArea.Width 
   >             : printableArea.Height));
   > 
   >     // Draw our rectangle which will either be the soft margin rectangle 
   >     // or the hard margin (printer capabilities) rectangle.
   >     // ----------
   >     // Note: we adjust the width and height minus one as it is a zero, 
   >     // zero based co-ordinates system. This will put the rectangle just 
   >     // inside the available width and height.
   >     g.DrawRectangle(Pens.Red, 0, 0, availableWidth - 1, availableHeight - 1);
   > }
   > ```

3. [PrintableArea in C# - Bug?](https://stackoverflow.com/questions/2595610/printablearea-in-c-sharp-bug)

4. Finally, C# supports `MM_HIMETRIC` : [PrinterUnit](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.printing.printerunit?view=net-5.0)
   
   > HundredthsOfAMillimeter: One-hundredth of a millimeter (0.01 mm).
   
   [PrinterUnitConvert](https://docs.microsoft.com/en-us/dotnet/api/system.drawing.printing.printerunitconvert?view=net-5.0)
   
   > Specifies a series of conversion methods that are useful when  interoperating with the Win32 printing API. This class cannot be  inherited.
   
   [GraphicsUnitConverter](https://docs.devexpress.com/CoreLibraries/DevExpress.XtraPrinting.GraphicsUnitConverter._members)

5. [Print Support - Windows Forms .NET Framework | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/windows-forms-print-support?view=netframeworkdesktop-4.8)
