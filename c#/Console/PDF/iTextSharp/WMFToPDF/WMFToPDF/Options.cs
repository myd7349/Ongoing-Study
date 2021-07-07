namespace WMFToPDF
{
    using CommandLine;

    class Options
    {
        [Option('i', "input", Required = true, HelpText = "Input WMF file.")]
        public string InputFilePath { get; set; }

        [Option('o', "output", HelpText = "Output PDF file path.")]
        public string OutputFilePath { get; set; }
    }
}
