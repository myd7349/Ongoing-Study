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

        [Option('r', "recursive", Default = false, HelpText = "Take parent position into account when using Bounds.")]
        public bool Recursive { get; set; }

        [Option('a', "abs", Default = false, HelpText = "Use AbsBounds instead of Bounds.")]
        public bool Abs { get; set; }

        [Option('p', "prepare", Default = false, HelpText = "Prepare the report.")]
        public bool Prepare { get; set; }
    }
}


// References:
// [Defining sets of valid option values](https://github.com/commandlineparser/commandline/issues/45)
