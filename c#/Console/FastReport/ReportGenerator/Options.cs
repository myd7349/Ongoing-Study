namespace ReportGenerator
{
    using System.Collections.Generic;

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

        [Option('p', "parameter", HelpText = "Specify report parameter(key=value).")]
        public IEnumerable<string> Parameters { get; set; }
    }
}
