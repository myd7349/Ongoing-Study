namespace EMFToPDF
{
    using System;
    using System.Collections.Generic;
    using System.IO;

    using CommandLine;
    using CommandLine.Text;

    using iText.IO.Image;
    using iText.Kernel.Pdf;
    using iText.Kernel.Pdf.Canvas.Wmf;
    using iText.Layout;
    using iText.Layout.Element;

    class Program
    {
        static void Main(string[] args)
        {
            var parser = new Parser(config => { config.HelpWriter = null; });
            var parserResult = parser.ParseArguments<Options>(args);
            parserResult
                .WithParsed(options => Run(options))
                .WithNotParsed(errors => DisplayHelp(parserResult, errors));
        }

        private static void Run(Options options)
        {
            try
            {
                Environment.Exit(RunInternal(options));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Failed to convert EMF file to PDF document \"{0}\":\n{1}",
                    options.OutputFilePath, ex);

                Environment.Exit(1);
            }
        }

        private static void DisplayHelp(ParserResult<Options> result, IEnumerable<Error> errors)
        {
            var helpText = HelpText.AutoBuild(result, h =>
            {
                h.AutoHelp = false;
                h.AutoVersion = false;
                h.AdditionalNewLineAfterOption = false;
                h.AddEnumValuesToHelpText = true;
                h.Heading = "EMF2PDF v0.1.0";
                h.Copyright = "Copyright (c) 2020 myd7349";
                return HelpText.DefaultParsingErrorsHandler(result, h);
            }, e => e);
            Console.WriteLine(helpText);
            Environment.Exit(1);
        }

        private static int RunInternal(Options options)
        {
            if (!File.Exists(options.InputFilePath))
            {
                Console.WriteLine("Input file \"{0}\" doesn't exist.", options.InputFilePath);
                return 1;
            }

            if (string.IsNullOrWhiteSpace(options.OutputFilePath))
            {
                options.OutputFilePath = Path.ChangeExtension(options.InputFilePath, ".pdf");
            }
            else if (Directory.Exists(options.OutputFilePath))
            {
                var intputFileNameWithoutExtension = Path.GetFileNameWithoutExtension(options.InputFilePath);
                options.OutputFilePath = Path.Combine(options.OutputFilePath, intputFileNameWithoutExtension + ".pdf");
            }
            else
            {
                var directoryName = Path.GetDirectoryName(options.OutputFilePath);
                var fileName = Path.GetFileName(options.OutputFilePath);

                if (!Directory.Exists(directoryName))
                    Directory.CreateDirectory(directoryName);

                if (string.IsNullOrEmpty(fileName))
                {
                    var intputFileNameWithoutExtension = Path.GetFileNameWithoutExtension(options.InputFilePath);
                    options.OutputFilePath = Path.Combine(directoryName, intputFileNameWithoutExtension + ".pdf");
                }
            }

            var metafile = new WmfImageData(options.InputFilePath);

            FileStream outFileStream;
            try
            {
                outFileStream = new FileStream(options.OutputFilePath, FileMode.CreateNew);
            }
            catch (IOException ex)
            {
                Console.WriteLine("Failed to create PDF document \"{0}\":\n{1}.",
                    options.OutputFilePath, ex);
                return 1;
            }

            var pdfWriter = new PdfWriter(outFileStream);

            var pdfDocument = new PdfDocument(pdfWriter);
            var document = new Document(pdfDocument);

            var image = new Image(metafile);
            document.Add(image);

            document.Close();

            return 0;
        }
    }
}

// References:
// [How to convert/add .wmf to .pdf](https://stackoverflow.com/questions/40608036/how-to-convert-add-wmf-to-pdf)
// [Adding a WMF to a PDF using iTextSharp](https://stackoverflow.com/questions/4935751/adding-a-wmf-to-a-pdf-using-itextsharp)
// [How to draw vector graphics and save it in PDF file?](https://stackoverflow.com/questions/30411854/how-to-draw-vector-graphics-and-save-it-in-pdf-file)
// [Which image types are supported by iText?](https://kb.itextpdf.com/home/it5kb/faq/which-image-types-are-supported-by-itext)
// [How to draw vector graphics and save it in PDF file?](https://stackoverflow.com/questions/30411854/how-to-draw-vector-graphics-and-save-it-in-pdf-file)
// >1. Use chart.SaveImage with one of the three emf formats.
//  2. Convert the resulting emf file to wmf
//  3. Insert the wmf file into your iTextSharp document.
// [Add an image to an existing PDF file with iText7](https://stackoverflow.com/questions/48251170/add-an-image-to-an-existing-pdf-file-with-itext7)
// [How to save a MS Chart in WMF format and insert in the PDF iTextSharp](https://stackoverflow.com/questions/43276550/how-to-save-a-ms-chart-in-wmf-format-and-insert-in-the-pdf-itextsharp)
// [iText7 Create PDF in memory instead of physical file](https://stackoverflow.com/questions/40540741/itext7-create-pdf-in-memory-instead-of-physical-file)
