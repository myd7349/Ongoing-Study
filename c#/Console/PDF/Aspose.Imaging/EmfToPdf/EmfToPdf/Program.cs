namespace EmfToPdf
{
    using System;
    using System.IO;

    using Aspose.Imaging;
    using Aspose.Imaging.ImageOptions;

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

            using (var metafile = Image.Load(inputEmfFilePath))
            {
                var options = new PdfOptions();
                metafile.Save(outputFilepath, options);
            }
        }
    }
}

// References:
// [Convert EMF to PDF via C#](https://products.aspose.com/imaging/net/conversion/emf-to-pdf/)
