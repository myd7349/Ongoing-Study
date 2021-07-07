namespace EmfToWmf
{
    using System;
    using System.Drawing.Imaging;
    using System.IO;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1 && args.Length != 2)
            {
                Console.WriteLine("Usage:\n\tEmfToWmf <input.emf> [output.wmf]\n");
                return;
            }

            var inputEmfFilePath = args[0];
            var outputWmfFilepath = args.Length == 2 ? args[1] : Path.ChangeExtension(inputEmfFilePath, ".wmf");

#if false
            using (var metafile = new Metafile(inputEmfFilePath))
                MetafileUtility.MetafileToWMF(metafile, outputWmfFilepath);
#else
            using (var metafile = new Metafile(inputEmfFilePath))
            using (var outputFile = new FileStream(outputWmfFilepath, FileMode.CreateNew))
            {
                var bytes = MetafileUtility.GetMetafileRawBytes(metafile);
                outputFile.Write(bytes, 0, bytes.Length);
            }
#endif
        }
    }
}

// References:
// [How to save a MS Chart in WMF format and insert in the PDF iTextSharp](https://stackoverflow.com/questions/43276550/how-to-save-a-ms-chart-in-wmf-format-and-insert-in-the-pdf-itextsharp)
// [Convert an image into WMF with .NET?](https://stackoverflow.com/questions/5270763/convert-an-image-into-wmf-with-net)
// [How to draw vector graphics and save it in PDF file?](https://stackoverflow.com/questions/30411854/how-to-draw-vector-graphics-and-save-it-in-pdf-file)
// https://www.pinvoke.net/default.aspx/gdiplus/GdipEmfToWmfBits.html
// [WMF / EMF File Format conversion C#](https://stackoverflow.com/questions/1763428/wmf-emf-file-format-conversion-c-sharp)
// [WMF file doesn't display correctly](http://itext-general.2136553.n4.nabble.com/WMF-file-doesn-t-display-correctly-td2283480.html)
