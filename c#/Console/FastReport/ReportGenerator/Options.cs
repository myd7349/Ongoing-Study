namespace ReportGenerator
{
    using System.Collections.Generic;
    using System.Drawing;

    using CommandLine;
    using FastReport.Export.Image;

    class Options
    {
        [Option('i', "input", Required = true, HelpText = "Input report template file path.")]
        public string InputRfxFilePath { get; set; }

        [Option('o', "output", HelpText = "Output file path.")]
        public string OutputFilePath { get; set; }

        [Option('f', "format", Default = ImageExportFormat.Metafile, HelpText = "Output file format.")]
        public ImageExportFormat Format { get; set; }

        [Option('r', "resolution", HelpText = "Output file resolution.")]
        public int Resolution { get; set; }

        [Option('x', "resolution-x", HelpText = "Output file resolution (horizontal).")]
        public int ResolutionX { get; set; }

        [Option('y', "resolution-y", HelpText = "Output file resolution (vertical).")]
        public int ResolutionY { get; set; }

        [Option('t', "transform", Default = RotateFlipType.RotateNoneFlipNone, HelpText = "Rotate or flip.")]
        public RotateFlipType RotateFlip { get; set; }

        [Option('p', "parameter", HelpText = "Specify report parameter (key=value).")]
        public IEnumerable<string> Parameters { get; set; }
    }
}
