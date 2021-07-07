namespace EmfToPdf
{
    using System;
    using System.Drawing;
    using System.IO;

    using Syncfusion.Pdf;
    using Syncfusion.Pdf.Graphics;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1 && args.Length != 2)
            {
                Console.WriteLine("Usage:\n\tEmfToPdf <input.emf> [output.pdf]\n");
                return;
            }

            var inputEmfFilePath = args[0];
            var outputFilepath = args.Length == 2 ? args[1] : Path.ChangeExtension(inputEmfFilePath, ".pdf");

            using (var pdfDocument = new PdfDocument())
            {
#if true
                var page = pdfDocument.Pages.Add();
#else
                var section = pdfDocument.Sections.Add();
                section.PageSettings.Rotate = PdfPageRotateAngle.RotateAngle90;
                var page = section.Pages.Add();
#endif
                var graphics = page.Graphics;

                var format = new PdfMetafileLayoutFormat
                {
                    SplitImages = true,
                    SplitTextLines = true,
                };

                var metafile = new PdfMetafile(inputEmfFilePath);
                metafile.Draw(page, PointF.Empty, format);

                pdfDocument.Save(outputFilepath);
            }
        }
    }
}

// References:
// [How to convert EMF to PDF using C# and VB.NET](https://www.syncfusion.com/kb/9546/how-to-convert-emf-to-pdf-using-c-and-vb-net)
// [How to rotate pages in a PDF file](https://www.syncfusion.com/kb/9154/how-to-rotate-pages-in-a-pdf-file)
