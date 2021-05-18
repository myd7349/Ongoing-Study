namespace HDF5.Extension
{
    using System;

    using HDF.PInvoke;

    using Common;

    public static partial class HDF5Helper
    {
        static HDF5Helper()
        {
            NumericTypeToHDF5TypeMap.Fill(-1);

            NumericTypeToHDF5TypeMap[(int)TypeCode.SByte] = H5T.NATIVE_INT8;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Byte] = H5T.NATIVE_UINT8;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Int16] = H5T.NATIVE_INT16;
            NumericTypeToHDF5TypeMap[(int)TypeCode.UInt16] = H5T.NATIVE_UINT16;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Int32] = H5T.NATIVE_INT32;
            NumericTypeToHDF5TypeMap[(int)TypeCode.UInt32] = H5T.NATIVE_UINT32;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Int64] = H5T.NATIVE_INT64;
            NumericTypeToHDF5TypeMap[(int)TypeCode.UInt64] = H5T.NATIVE_UINT64;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Single] = H5T.NATIVE_FLOAT;
            NumericTypeToHDF5TypeMap[(int)TypeCode.Double] = H5T.NATIVE_DOUBLE;
        }
    }
}

