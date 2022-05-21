<Query Kind="Statements">
  <NuGetReference>OxyPlot.Core</NuGetReference>
  <NuGetReference>OxyPlot.WindowsForms</NuGetReference>
  <Namespace>OxyPlot</Namespace>
  <Namespace>OxyPlot.Axes</Namespace>
  <Namespace>OxyPlot.Series</Namespace>
  <Namespace>OxyPlot.WindowsForms</Namespace>
</Query>

var model = new PlotModel { Title = "ScatterSeries" };
var scatterSeries = new ScatterSeries { MarkerType = MarkerType.Circle };
var r = new Random(314);
for (int i = 0; i < 100; i++)
{
    var x = r.NextDouble();
    var y = r.NextDouble();
    var size = r.Next(5, 15);
    var colorValue = r.Next(100, 1000);
    scatterSeries.Points.Add(new ScatterPoint(x, y, size, colorValue));
}

model.Series.Add(scatterSeries);
model.Axes.Add(new LinearColorAxis { Position = AxisPosition.Right, Palette = OxyPalettes.Jet(200) });

var plot = new PlotView { Model = model };
plot.Dump();

// References:
// [OxyPlot sample applied on OxyPlot WPF renders blank](https://forum.linqpad.net/discussion/184/oxyplot-sample-applied-on-oxyplot-wpf-renders-blank)
// share.linqpad.net/2529v5.linq
// https://www.linqpad.net/customvisualizers.aspx
// [Example of OxyPlot.Wpf renders blank](https://forum.linqpad.net/discussion/2658/example-of-oxyplot-wpf-renders-blank)
