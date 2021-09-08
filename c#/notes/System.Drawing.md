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