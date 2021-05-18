namespace HDF5.Extension
{
    using System;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        private static readonly hid_t[] NumericTypeToHDF5TypeMap = new hid_t[Enum.GetValues(typeof(TypeCode)).Length];
    }
}
