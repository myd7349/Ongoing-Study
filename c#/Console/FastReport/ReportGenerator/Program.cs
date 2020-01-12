namespace ReportGenerator
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.IO;

    using CommandLine;
    using CommandLine.Text;
    using FastReport;
    using FastReport.Export.Image;

    class Program
    {
        static void Main(string[] args)
        {
            var parser = new Parser(config => { config.HelpWriter = null; });
            var parserResult = parser.ParseArguments<Options>(args);
            parserResult
                .WithParsed<Options>(options => Run(options))
                .WithNotParsed<Options>(errors => DisplayHelp(parserResult, errors));
        }

        private static void Run(Options options)
        {
            try
            {
                Environment.Exit(RunInternal(options));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Failed to render report to file \"{0}\":\n{1}",
                    options.InputRfxFilePath, ex);

                Environment.Exit(1);
            }
        }

        private static int RunInternal(Options options)
        {
            if (!File.Exists(options.InputRfxFilePath))
            {
                Console.WriteLine("Input file \"{0}\" doesn't exist.",
                    options.InputRfxFilePath);
                return 1;
            }

            using (var report = new Report())
            {
                try
                {
                    report.Load(options.InputRfxFilePath);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Failed to load report template \"{0}\":\n{1}",
                        options.InputRfxFilePath, ex);
                    return 1;
                }

                foreach (var parameter in options.Parameters)
                {
                    var parameterParts = parameter.Split(new char[] { '=' }, 2);
                    if (parameterParts.Length != 2 || string.IsNullOrWhiteSpace(parameterParts[0]))
                    {
                        Console.WriteLine("Invalid parameter: {0}.", parameter);
                        return 1;
                    }

                    Console.WriteLine("Parameter: {0}={1}", parameterParts[0], parameterParts[1]);
                    report.SetParameterValue(parameterParts[0], parameterParts[1]);
                }

                if (!report.Prepare())
                {
                    Console.WriteLine("Failed to prepare report.");
                    return 1;
                }

                if (string.IsNullOrWhiteSpace(options.OutputFilePath))
                {
                    string extension = ImageFormatToExtension(options.Format);
                    if (string.IsNullOrWhiteSpace(extension))
                    {
                        Console.WriteLine("Unknown image format \"{0}\".", options.Format);
                        return 1;
                    }

                    var directory = Path.GetDirectoryName(options.InputRfxFilePath);
                    var fileNameWithoutExtension = Path.GetFileNameWithoutExtension(options.InputRfxFilePath);

                    var outputFilePath = Path.Combine(directory, fileNameWithoutExtension + extension);
                    int id = 1;
                    while (File.Exists(outputFilePath))
                    {
                        if (id == int.MaxValue)
                        {
                            Console.WriteLine("Can not find a proper output file name.");
                            return 1;
                        }

                        Console.WriteLine("File \"{0}\" already exist.", outputFilePath);
                        outputFilePath = Path.Combine(directory,
                            fileNameWithoutExtension +
                            " (" + id.ToString() + ")" +
                            extension);

                        id++;
                    }

                    options.OutputFilePath = outputFilePath;
                }

                using (var imageExporter = new ImageExport())
                {
                    imageExporter.ImageFormat = options.Format;
                    if (options.Resolution > 0)
                        imageExporter.Resolution = options.Resolution;

                    report.Export(imageExporter, options.OutputFilePath);
                }
            }

            if (options.RotateFlip != RotateFlipType.RotateNoneFlipNone)
            {
                using (var bitmap = Bitmap.FromFile(options.OutputFilePath))
                {
                    bitmap.RotateFlip(options.RotateFlip);
                    bitmap.Save(options.OutputFilePath);
                }
            }

            return 0;
        }

        private static string ImageFormatToExtension(ImageExportFormat format)
        {
            switch (format)
            {
                case ImageExportFormat.Bmp: return ".bmp";
                case ImageExportFormat.Gif: return ".gif";
                case ImageExportFormat.Jpeg: return ".jpg";
                case ImageExportFormat.Metafile: return ".emf";
                case ImageExportFormat.Png: return ".png";
                case ImageExportFormat.Tiff: return ".tiff";
            }

            return "";
        }

        private static void DisplayHelp(ParserResult<Options> result, IEnumerable<Error> errors)
        {
            var helpText = HelpText.AutoBuild(result, h =>
            {
                h.AutoHelp = false;
                h.AutoVersion = false;
                h.AdditionalNewLineAfterOption = false;
                h.AddEnumValuesToHelpText = true;
                h.Heading = "ReportGenerator v0.1.0";
                h.Copyright = "Copyright (c) 2020 myd7349";
                return HelpText.DefaultParsingErrorsHandler(result, h);
            }, e => e);
            Console.WriteLine(helpText);
            Environment.Exit(1);
        }
    }
}

// References:
// [How do I specify the exit code of a console application in .NET?](https://stackoverflow.com/questions/155610/how-do-i-specify-the-exit-code-of-a-console-application-in-net)
// [How do I rotate a picture in WinForms](https://stackoverflow.com/questions/2163829/how-do-i-rotate-a-picture-in-winforms)
// [in C# how to rotate picturebox with its image?](https://stackoverflow.com/questions/5016081/in-c-sharp-how-to-rotate-picturebox-with-its-image)
// [How to rotate an ATL::CImage object](https://stackoverflow.com/questions/9492169/how-to-rotate-an-atlcimage-object)
