namespace FastReportDemo
{
    using System.Collections.Generic;

    using FastReport;
    using FastReport.Export.Image;

    class Program
    {
        static void Main(string[] args)
        {
            using (var report = new Report())
            {
                var movie = new Movie
                {
                    SN = "tt1979376",
                    Name = "Toy Story 4",
                    Director = "Josh Cooley",
                    EstimatedBudget = "$200,000,000",
                    ReleaseDate = "21 June 2019"
                };

                var movies = new List<Movie>
                {
                    movie
                };

                report.Load("report.frx");
                report.RegisterData(movies, "Movies");
                report.Prepare();

                using (var imageExporter = new ImageExport())
                {
                    imageExporter.ImageFormat = ImageExportFormat.Metafile;
                    imageExporter.Resolution = 72;

                    report.Export(imageExporter, "report.emf");
                }
            }
        }
    }
}

// References:
// https://github.com/FastReports/FastReport.Documentation/blob/master/Exporting.md
// https://github.com/FastReports/FastReport/tree/master/Demos/OpenSource/DataFromBusinessObject
