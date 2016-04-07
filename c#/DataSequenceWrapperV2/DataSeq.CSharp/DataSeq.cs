// 2016-03-25T13:07+08:00
using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Security;

namespace DataSeq.CSharp
{
    using DataSeqHandle = System.IntPtr;

    // A wrapper class for DataSeq.dll.
    internal sealed class DataSeq
    {
        public enum Error
        {
            NoError = 0,
            IndexOutOfRange = 1,
            InvalidParameter = 2,
            InvalidOperation = 3,
            MemoryError = 4,
            UnknownError = 5,
        }

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Create")]
        public static extern Error Create(ref DataSeqHandle dataSeq, UInt32 size);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PushBack")]
        public static extern Error PushBack(DataSeqHandle dataSeq, double v);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_PopBack")]
        public static extern Error PopBack(DataSeqHandle dataSeq, ref double v);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetSize")]
        public static extern Error GetSize(DataSeqHandle dataSeq, ref UInt32 size);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetAt")]
        public static extern Error GetAt(DataSeqHandle dataSeq, UInt32 i, ref double v);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_SetAt")]
        public static extern Error SetAt(DataSeqHandle dataSeq, UInt32 i, double v);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_GetData")]
        public static extern Error GetData(DataSeqHandle dataSeq, ref IntPtr pData);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("DataSeq.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "DataSeq_Free")]
        public static extern void Free(DataSeqHandle dataSeq);
    }

    public sealed class DataSequence : IDisposable, IEnumerable
    {
        private DataSeqHandle dataSeqHandle;

        public DataSequence(UInt32 size = 0)
        {
            Validate(DataSeq.Create(ref dataSeqHandle, size), false);
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
                Validate(DataSeq.GetSize(dataSeqHandle, ref size));
                return size;
            }
        }

        public double this[UInt32 i]
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
            Validate(DataSeq.GetData(dataSeqHandle, ref unmanagedDataPtr));

            double[] managedDataBuf = new double[Size];
            Marshal.Copy(unmanagedDataPtr, managedDataBuf, 0, managedDataBuf.Length);
            return managedDataBuf;
        }

        public IEnumerator GetEnumerator()
        {
            var data = GetData();
            if (data == null)
                throw new Exception("Invalid data sequence handle.");

            foreach (var v in data)
                yield return v;
        }

        public void Dispose()
        {
            Debug.WriteLine("Calling DataSeq_Free...");

            if (IsValid)
                DataSeq.Free(dataSeqHandle);
        }

        private bool IsValid
        {
            get { return dataSeqHandle != DataSeqHandle.Zero; }
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
                    default: Debug.Assert(false); break;
                }
            }
        }
    }
}

// References:
// [sqlite-net](https://github.com/koush/sqlite-net)