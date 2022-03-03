namespace ReportGenerator
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Xml.Linq;

    using CommandLine;
    using CommandLine.Text;
    using FastReport;
    using FastReport.Export;
    using FastReport.Export.Image;
    using FastReport.Export.PdfSimple;

    using Common;

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
                    options.OutputFilePath, ex);

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

            string baseReportFilePath;
            var isInheritedReport = TryGetBaseReportFilePath(
                options.InputRfxFilePath, out baseReportFilePath);

            using (var report = new Report())
            {
                if (isInheritedReport)
                {
#if true
                    try
                    {
                        report.Load(baseReportFilePath);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Failed to load base report template \"{0}\":\n{1}",
                            baseReportFilePath, ex);
                        return 1;
                    }
#else
                    Func<object, CustomLoadEventArgs> loadBaseReport = (sender, e)
                    {
                        e.Report.Load(baseReportFilePath);
                    };

                    report.LoadBaseReport += new CustomLoadEventHandler(loadBaseReport);
                    report.LoadBaseReport -= new CustomLoadEventHandler(loadBaseReport);
#endif
                }

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

#if DEBUG
                Console.WriteLine("Report filename: {0}.", report.FileName);
                Console.WriteLine("Base report filename: {0}.", report.BaseReport);
#endif

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

                foreach (var picture in options.Pictures)
                {
                    var parts = picture.Split(new char[] { '=' }, 2);
                    if (parts.Length != 2 || string.IsNullOrWhiteSpace(parts[0]))
                    {
                        Console.WriteLine("Invalid picture object name-location pair: {0}.", picture);
                        return 1;
                    }

                    var pictureObjectName = parts[0];
                    var pictureLocation = parts[1];

                    var reportObject = report.FindObject(pictureObjectName);
                    if (reportObject == null)
                    {
                        Console.WriteLine("Couldn't find a picture object with name: {0}.", pictureObjectName);
                        return 1;
                    }

                    var pictureObject = reportObject as PictureObject;
                    if (pictureObject == null)
                    {
                        Console.WriteLine("Object \"{0}\" is not a picture object.", pictureObjectName);
                        return 1;
                    }

                    Image image = null;
                    if (!string.IsNullOrEmpty(pictureLocation))
                    {
                        if (File.Exists(pictureLocation))
                        {
                            try
                            {
                                image = Image.FromFile(pictureLocation);
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine("Failed to load picture from location {0}:\r\n{1}",
                                    pictureLocation, ex.ToString());
                            }
                        }
                        else if (Base64Helper.IsBase64String(pictureLocation))
                        {
                            try
                            {
                                image = ImageHelper.LoadFromBase64(pictureLocation);
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine("Failed to load picture from base64 string {0}:\r\n{1}.",
                                    pictureLocation, ex.ToString());
                            }
                        }
                        else
                        {
                            Console.WriteLine("Picture file \"{0}\" doesn't exist.", pictureLocation);
                        }
                    }

                    pictureObject.Image = image;
                }

                if (!report.Prepare())
                {
                    Console.WriteLine("Failed to prepare report.");
                    return 1;
                }

                if (string.IsNullOrWhiteSpace(options.OutputFilePath))
                {
                    string extension = FormatHelper.ExportFormatToExtension(options.Format);
                    if (string.IsNullOrWhiteSpace(extension))
                    {
                        Console.WriteLine("Unknown export format \"{0}\".", options.Format);
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
                else
                {
                    string extension = Path.GetExtension(options.OutputFilePath);
                    if (!string.IsNullOrEmpty(extension))
                    {
                        // .\ReportGenerator.exe -i in.frx -o out.pdf
                        // will generate a .emf file, not a PDF file.
                        // So we need to fix it.
                        var expectedFormat = FormatHelper.ExportFormatFromExtension(extension);
                        if (expectedFormat != ExportFormat.Invalid && options.Format != expectedFormat)
                        {
                            if (options.Format != ExportFormat.Metafile)
                            {
                                Console.WriteLine("Incompatible formats are detected:\r\nFormat specified: {0}\r\nFormat guessed from extension: {1}\r\n",
                                    options.Format, expectedFormat);
                            }

                            options.Format = expectedFormat;
                        }
                    }
                }

                if (options.Format == ExportFormat.Invalid)
                {
                    Console.WriteLine("Invalid export format: {0}.", options.Format);
                    return 1;
                }

                if (options.Format == ExportFormat.Pdf)
                {
                    using (var pdfExporter = new PDFSimpleExport())
                    {
                        if (options.Resolution > 0)
                            pdfExporter.ImageDpi = options.Resolution;

                        if (options.Quality >= 0 && options.Quality <= 100)
                            pdfExporter.JpegQuality = options.Quality;

                        report.Export(pdfExporter, options.OutputFilePath);
                    }
                }
                else
                {
                    using (var imageExporter = new ImageExport())
                    {
                        imageExporter.ImageFormat = FormatHelper.ExportFormatToImageExportFormat(options.Format);

                        // FastReport uses 96 DPI by default. If you specify a different
                        // DPI (e.g. 600 dpi, which is common for printers) here, FastReport
                        // will do some coordinate conversion when generating reports.
                        // In some older versions of FastReport, there is a problem when
                        // doing coordinate conversion, which results in incorrectly sized
                        // reports being generated.
                        // A test:
                        // ..\Templates\different_dpi_test.bat
                        // It seems that we can not change the DPI of output Metafile, however.
                        //
                        // [Export to Picture](https://www.fast-report.com/documentation/UserManFrNET-en/index.html?exporttoimage.htm)
                        // > "Resolution" - resolution of the graphical image.
                        // > Use 96dpi for displaying, 300dpi for printing.
                        // > When exporting into the TIFF format, you will able to
                        // > set separate values for horizontal and vertical resolution.
                        if (options.Resolution > 0)
                        {
                            imageExporter.Resolution = options.Resolution;
                        }
                        else if (options.ResolutionX > 0 && options.ResolutionY > 0)
                        {
                            imageExporter.ResolutionX = options.ResolutionX;
                            imageExporter.ResolutionY = options.ResolutionY;
                        }

                        if (options.Quality >= 0 && options.Quality <= 100)
                            imageExporter.JpegQuality = options.Quality;

                        report.Export(imageExporter, options.OutputFilePath);
                    }

                    if (options.RotateFlip != RotateFlipType.RotateNoneFlipNone)
                    {
                        using (var bitmap = Bitmap.FromFile(options.OutputFilePath))
                        {
                            bitmap.RotateFlip(options.RotateFlip);
                            bitmap.Save(options.OutputFilePath);
                        }
                    }
                }
            }

            return 0;
        }

        private static bool TryGetBaseReportFilePath(string inheritedReportFilePath, out string baseReportFilePath)
        {
            if (string.IsNullOrEmpty(inheritedReportFilePath))
                throw new ArgumentException("inheritedReportFilePath");

            var document = XDocument.Load(inheritedReportFilePath);
            var rootElement = document.Root;

            switch (rootElement.Name.LocalName)
            {
                case "Report":
                    baseReportFilePath = null;
                    return false;
                case "inherited":
                    break;
                default:
                    throw new InvalidOperationException("Not a valid FastReport template file.");
            }

            var baseReportAttribute = rootElement.Attribute("BaseReport");
            if (baseReportAttribute == null)
                throw new InvalidOperationException("BaseReport attribute is missing.");

            baseReportFilePath = baseReportAttribute.Value;
            if (File.Exists(baseReportFilePath))
            {
                baseReportFilePath = Path.GetFullPath(baseReportFilePath);
                return true;
            }
            else
            {
                baseReportFilePath = Path.Combine(
                    Path.GetDirectoryName(inheritedReportFilePath),
                    baseReportFilePath);
                if (File.Exists(baseReportFilePath))
                    return true;

                var baseReportAbsolutePathAttribute = rootElement.Attribute("BaseReportAbsolutePath");
                if (baseReportAbsolutePathAttribute == null)
                {
                    baseReportFilePath = null;
                    return false;
                }

                baseReportFilePath = baseReportAbsolutePathAttribute.Value;
                if (File.Exists(baseReportFilePath))
                {
                    return true;
                }
                else
                {
                    baseReportFilePath = null;
                    return false;
                }
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
// [Export FASTREPORT print as PDF](https://stackoverflow.com/questions/16895574/export-fastreport-print-as-pdf/17004059)
// [How to set a picture in a report from the user application code](https://www.fast-report.com/en/blog/show/picture-from-user-code/)
// [How do I get the XML root node with C#?](https://stackoverflow.com/questions/4498423/how-do-i-get-the-xml-root-node-with-c)
// [How to inherit report from code?](https://www.fast-report.com/en/faq/18/249/)
// [How to make report inheritance in FastReport.NET](https://www.fast-report.com/en/blog/show/report-inheritance-fastreport-net/)
// [Storing a Lambda Expression in a Variable](https://stackoverflow.com/questions/4379048/storing-a-lambda-expression-in-a-variable)
