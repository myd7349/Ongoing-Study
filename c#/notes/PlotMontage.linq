<Query Kind="Statements">
  <NuGetReference>OxyPlot.Core</NuGetReference>
  <NuGetReference>OxyPlot.WindowsForms</NuGetReference>
  <Namespace>OxyPlot</Namespace>
  <Namespace>OxyPlot.Axes</Namespace>
  <Namespace>OxyPlot.Series</Namespace>
  <Namespace>OxyPlot.WindowsForms</Namespace>
  <Namespace>System.Drawing</Namespace>
  <RemoveNamespace>System.Collections</RemoveNamespace>
  <RemoveNamespace>System.Data</RemoveNamespace>
  <RemoveNamespace>System.Diagnostics</RemoveNamespace>
  <RemoveNamespace>System.IO</RemoveNamespace>
  <RemoveNamespace>System.Linq</RemoveNamespace>
  <RemoveNamespace>System.Linq.Expressions</RemoveNamespace>
  <RemoveNamespace>System.Reflection</RemoveNamespace>
  <RemoveNamespace>System.Text</RemoveNamespace>
  <RemoveNamespace>System.Text.RegularExpressions</RemoveNamespace>
  <RemoveNamespace>System.Threading</RemoveNamespace>
  <RemoveNamespace>System.Transactions</RemoveNamespace>
  <RemoveNamespace>System.Xml</RemoveNamespace>
  <RemoveNamespace>System.Xml.Linq</RemoveNamespace>
  <RemoveNamespace>System.Xml.XPath</RemoveNamespace>
</Query>

var positions = new Dictionary<string, PointF>(StringComparer.OrdinalIgnoreCase)
{
    ["Fp1"] = new PointF(-0.0294367f, 0.08391710000000001f),
    ["Fp2"] = new PointF(0.029872299999999997f, 0.0848959f),
    ["F3"] = new PointF(-0.0502438f, 0.0531112f),
    ["F4"] = new PointF(0.0518362f, 0.0543048f),
    ["C3"] = new PointF(-0.06535809999999999f, -0.0116317f),
    ["C4"] = new PointF(0.06711790000000001f, -0.0109003f),
    ["P3"] = new PointF(-0.0530073f, -0.0787878f),
    ["P4"] = new PointF(0.0556667f, -0.0785602f),
    ["O1"] = new PointF(-0.0294134f, -0.112449f),
    ["O2"] = new PointF(0.0298426f, -0.112156f),
    ["A1"] = new PointF(-0.0860761f, -0.0249897f),
    ["A2"] = new PointF(0.08579389999999999f, -0.025009299999999998f),
    ["F7"] = new PointF(-0.0702629f, 0.0424743f),
    ["F8"] = new PointF(0.0730431f, 0.0444217f),
    ["T3"] = new PointF(-0.0841611f, -0.0160187f),
    ["T4"] = new PointF(0.0850799f, -0.0150203f),
    ["T5"] = new PointF(-0.0724343f, -0.0734527f),
    ["T6"] = new PointF(0.0730557f, -0.07306829999999999f),
    ["Fz"] = new PointF(0.0003122f, 0.058512f),
    ["Cz"] = new PointF(0.0004009f, -0.009167f),
    ["Pz"] = new PointF(0.0003247f, -0.08111499999999999f),
};

var model = new PlotModel { Title = "Sensor Positions" };
var scatterSeries = new ScatterSeries { MarkerType = MarkerType.Circle };

foreach (var kv in positions)
{
    scatterSeries.Points.Add(new ScatterPoint(kv.Value.X, kv.Value.Y, 20, 0));
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
