// 2016-03-16T14:52+08:00
using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;


// A wrapper class for DataSequence.dll.

internal sealed class DataSeq
{
    public enum Error
    {
        NoError          = 0,
        IndexOutOfRange  = 1,
        InvalidParameter = 2,
        InvalidOperation = 3,
        MemoryError      = 4,
        UnknownError     = 5,
    };

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Create")]
    public static extern Error Create(ref IntPtr dataSeq, UInt32 size);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PushBack")]
    public static extern Error PushBack(IntPtr dataSeq, double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PopBack")]
    public static extern Error PopBack(IntPtr dataSeq, ref double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetSize")]
    public static extern Error Size(IntPtr dataSeq, ref UInt32 size);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetAt")]
    public static extern Error GetAt(IntPtr dataSeq, UInt32 i, ref double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_SetAt")]
    public static extern Error SetAt(IntPtr dataSeq, UInt32 i, double v);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetData")]
    public static extern Error Data(IntPtr dataSeq, ref IntPtr pData);

    [DllImport("DataSequence.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Free")]
    public static extern void Free(IntPtr dataSeq);
};

public sealed class DataSequence : IDisposable, IEnumerable
{
    private IntPtr dataSeqHandle;

    public DataSequence(UInt32 size = 0)
    {
        DataSeq.Error error = DataSeq.Create(ref dataSeqHandle, size);
        Validate(error, false);
    }

    public void PushBack(double v)
    {
        Validate(DataSeq.PushBack(dataSeqHandle, v));
    }

    public void PopBack()
    {
        double v = 0.0;
        Validate(DataSeq.PopBack(dataSeqHandle, ref v));
    }

    public UInt32 Size
    {
        get
        {
            UInt32 size = 0;
            Validate(DataSeq.Size(dataSeqHandle, ref size));
            return size;
        }
    }

    public double this [UInt32 i]
    {
        get
        {
            double v = 0.0;
            Validate(DataSeq.GetAt(dataSeqHandle, i, ref v));
            return v;
        }

        set
        {
            Validate(DataSeq.SetAt(dataSeqHandle, i, value));
        }
    }

    public double[] GetData()
    {
        UInt32 size = Size;
        if (size == 0)
            return null;

        IntPtr unmanagedDataPtr = IntPtr.Zero;
        Validate(DataSeq.Data(dataSeqHandle, ref unmanagedDataPtr));

        double[] managedDataBuf = new double[Size];
        Marshal.Copy(unmanagedDataPtr, managedDataBuf, 0, managedDataBuf.Length);
        return managedDataBuf;
    }

    public void Dispose()
    {
        Debug.WriteLine("Calling DataSeq_Free...");

        if (IsValid)
            DataSeq.Free(dataSeqHandle);
    }

    public IEnumerator GetEnumerator()
    {
        var data = GetData();
        if (data == null)
            throw new Exception("Invalid data sequence handle.");

        foreach (var v in data)
            yield return v;
    }

    private bool IsValid
    {
        get { return dataSeqHandle != IntPtr.Zero; }
    }

    private void Validate(DataSeq.Error error, bool throwException = true)
    {
        Debug.Assert(error == DataSeq.Error.NoError);

        if (throwException && error != DataSeq.Error.NoError)
        {
            switch (error)
            {
                case DataSeq.Error.IndexOutOfRange:
                    throw new IndexOutOfRangeException();
                case DataSeq.Error.InvalidParameter:
                    throw new Exception("DataSeq.Error.InvalidParameter");
                case DataSeq.Error.InvalidOperation:
                    throw new Exception("DataSeq.Error.InvalidOperation");
                case DataSeq.Error.MemoryError:
                    throw new OutOfMemoryException();
                case DataSeq.Error.UnknownError:
                    throw new Exception("DataSeq.Error.UnknownError");
                default: Debug.Assert(false);  break;
            }
        }
    }
};

// References:
// [PInvoke Interop Assistant](http://clrinterop.codeplex.com/releases/view/14120)
// [How to import void * C API into C#?](http://stackoverflow.com/questions/521774/how-to-import-void-c-api-into-c)
// [Using Platform Invoke](http://www.codeproject.com/Articles/4965/Using-Platform-Invoke)
// [PInvoke - How to convert IntPtr to double[]?](https://social.msdn.microsoft.com/Forums/vstudio/en-US/2fa0c961-45f2-474f-9eeb-8cb73ece6eb5/pinvoke-how-to-convert-intptr-to-double?forum=netfxbcl)
// [Marshal.Copy Method](https://msdn.microsoft.com/library/ms146633%28v=vs.100%29.aspx)