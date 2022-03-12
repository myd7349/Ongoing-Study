namespace FakeAD
{
    interface IDataGenerator
    {
        int Samples { get; }

        double Next();
    }
}

// References:
// [Simple Signal Generator](https://www.codeproject.com/Articles/30180/Simple-Signal-Generator)
// https://github.com/mathnet/mathnet-filtering/tree/master/src/Filtering/DataSources
// https://github.com/ScottPlot/ScottPlot/blob/d3b9c13b67d0344cf68e6e1cb7893fc0f1785e7f/src/ScottPlot4/ScottPlot/DataGen.cs#L807-L1007
