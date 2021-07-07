namespace WMFToPDF
{
    using System;
    using System.Collections.Generic;
    using System.IO;

    using CommandLine;
    using CommandLine.Text;

    using iTextSharp.text;
    using iTextSharp.text.pdf;

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
                Console.WriteLine("Failed to convert WMF file to PDF document \"{0}\":\n{1}",
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
                h.Heading = "WMF2PDF v0.1.0";
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

            var metafile = ImgWMF.GetInstance(options.InputFilePath);

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

            var document = new Document();
            PdfWriter.GetInstance(document, outFileStream);
            document.Open();
            document.Add(metafile);
            document.Close();

            return 0;
        }
    }
}


// References:
// [How to convert/add .wmf to .pdf](https://stackoverflow.com/questions/40608036/how-to-convert-add-wmf-to-pdf)
// [Adding a WMF to a PDF using iTextSharp](https://stackoverflow.com/questions/4935751/adding-a-wmf-to-a-pdf-using-itextsharp)
// [How to draw vector graphics and save it in PDF file?](https://stackoverflow.com/questions/30411854/how-to-draw-vector-graphics-and-save-it-in-pdf-file)
