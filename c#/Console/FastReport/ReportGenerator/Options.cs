namespace ReportGenerator
{
    using System.Collections.Generic;
    using System.Drawing;

    using CommandLine;

    class Options
    {
        [Option('i', "input", Required = true, HelpText = "Input report template file path.")]
        public string InputRfxFilePath { get; set; }

        [Option('o', "output", HelpText = "Output file path.")]
        public string OutputFilePath { get; set; }

        [Option('f', "format", Default = ExportFormat.Metafile, HelpText = "Output file format.")]
        public ExportFormat Format { get; set; }

        [Option('r', "resolution", HelpText = "Output file resolution.")]
        public int Resolution { get; set; }

        [Option('x', "resolution-x", HelpText = "Output TIFF file resolution (horizontal).")]
        public int ResolutionX { get; set; }

        [Option('y', "resolution-y", HelpText = "Output TIFF file resolution (vertical).")]
        public int ResolutionY { get; set; }

        [Option('q', "quality", Default = -1, HelpText = "Jpeg Quality.")]
        public int Quality { get; set; }

        [Option('t', "transform", Default = RotateFlipType.RotateNoneFlipNone, HelpText = "Rotate or flip.")]
        public RotateFlipType RotateFlip { get; set; }

        [Option('p', "parameter", HelpText = "Specify report parameter (key=value).")]
        public IEnumerable<string> Parameters { get; set; }

        [Option("picture", HelpText = "Specify picture object location (name=location).")]
        public IEnumerable<string> Pictures { get; set; }
    }
}


// References:
// [System.Drawing.Common only supported on Windows](https://docs.microsoft.com/en-us/dotnet/core/compatibility/core-libraries/6.0/system-drawing-common-windows-only)
