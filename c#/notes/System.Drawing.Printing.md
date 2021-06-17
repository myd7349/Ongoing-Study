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

