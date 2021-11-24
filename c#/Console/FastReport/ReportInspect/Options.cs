namespace ReportInspect
{
    using CommandLine;

    class Options
    {
        [Option('t', "template", Required = true, HelpText = "FastReport template file path.")]
        public string TemplateFilePath { get; set; }

        [Option('n', "name", HelpText = "Report object name.")]
        public string ObjectName { get; set; }

        [Option('s', "separator", Default = " ", HelpText = "Value separator.")]
        public string Separator { get; set; }

        [Option('u', "unit", Default = Unit.Dots, HelpText = "Unit.")]
        public Unit Unit { get; set; }

        [Option('m', "margin", Default = false, HelpText = "Take report page margins in to consideration.")]
        public bool Margin { get; set; }
    }
}


// References:
// [Defining sets of valid option values](https://github.com/commandlineparser/commandline/issues/45)
