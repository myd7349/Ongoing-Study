// 2016-04-26T11:53+08:00
using Common;

static class Program
{
    static void Main()
    {
        const int Length = 512;
        const int Repeat = 10000;

        CopyArray.SWIGTYPE_p_double sourceArrayPtr = CopyArray.CopyArrayNative.new_doubleArray(Length);
        CopyArray.SWIGTYPE_p_double targetArrayPtr = CopyArray.CopyArrayNative.new_doubleArray(Length);

        double[] sourceArray = new double[Length];
        double[] targetArray = new double[Length];

        Util.BenchmarkHelper("CopyArray",
            () => CopyArray.CopyArrayNative.CopyArray(
                sourceArrayPtr, targetArrayPtr, Length),
            Repeat);
        CopyArray.CopyArrayNative.delete_doubleArray(sourceArrayPtr);
        CopyArray.CopyArrayNative.delete_doubleArray(targetArrayPtr);

        Util.BenchmarkHelper("CopyArray Via P/Invoke's Default Array Marshalling",
            () => DefaultArrayMarshalling.CopyArrayNative.CopyArray(
                sourceArray, targetArray, sourceArray.Length),
            Repeat);

        Util.BenchmarkHelper("CopyArray Via Pinned Array",
            () => PinnedArray.CopyArrayNative.CopyArray(
                sourceArray, targetArray, sourceArray.Length),
            Repeat);

        Util.Pause();
    }
}

