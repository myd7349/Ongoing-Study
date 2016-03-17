// 2016-03-16T14:52+08:00
using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;


// A wrapper class for DataSequence.dll.

public sealed class DataSequence
{
    public enum Error
    {
        NoError          = 0,
        IndexOutOfRange  = 1,
        InvalidParameter = 2,
        MemoryError      = 3,
        UnknownError     = 4,
    };

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Create")]
    public static extern Error DataSeq_Create(ref IntPtr dataSeq, UInt32 size);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PushBack")]
    public static extern Error DataSeq_PushBack(IntPtr dataSeq, double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PopBack")]
    public static extern Error DataSeq_PopBack(IntPtr dataSeq, ref double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Size")]
    public static extern Error DataSeq_Size(IntPtr dataSeq, ref UInt32 size);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetAt")]
    public static extern Error DataSeq_GetAt(IntPtr dataSeq, UInt32 i, ref double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_SetAt")]
    public static extern Error DataSeq_SetAt(IntPtr dataSeq, UInt32 i, double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Free")]
    public static extern void DataSeq_Free(IntPtr dataSeq);
};

public sealed class DataSeq : IDisposable, IEnumerable
{
    private IntPtr dataSeq;

    public DataSeq(UInt32 size = 0)
    {
        DataSequence.Error error = DataSequence.DataSeq_Create(ref dataSeq, size);
    }

    public void PushBack(double v)
    {
        if (dataSeq != IntPtr.Zero)
        {
            DataSequence.Error error = DataSequence.DataSeq_PushBack(dataSeq, v);
            Debug.Assert(error == DataSequence.Error.NoError);
        }
    }

    public void PopBack()
    {
        if (dataSeq != IntPtr.Zero)
        {
            double v = 0.0;
            DataSequence.Error error = DataSequence.DataSeq_PopBack(dataSeq, ref v);
            Debug.Assert(error == DataSequence.Error.NoError);
        }
    }

    public void Dispose()
    {
        Debug.WriteLine("Calling DataSeq_Free...");

        if (dataSeq != IntPtr.Zero)
            DataSequence.DataSeq_Free(dataSeq);
    }

    public IEnumerator GetEnumerator()
    {
        if (dataSeq != IntPtr.Zero)
        {
            UInt32 size = 0;
            DataSequence.Error error = DataSequence.DataSeq_Size(dataSeq, ref size);
            if (error == DataSequence.Error.NoError)
            {
                for (UInt32 i = 0; i < size; i++)
                {
                    double v = 0.0;
                    error = DataSequence.DataSeq_GetAt(dataSeq, i, ref v);
                    if (error == DataSequence.Error.NoError)
                        yield return v;
                }
            }
        }
    }
};

// References:
// [How to import void * C API into C#?](http://stackoverflow.com/questions/521774/how-to-import-void-c-api-into-c)
