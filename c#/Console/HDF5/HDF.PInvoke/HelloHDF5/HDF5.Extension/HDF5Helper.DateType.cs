namespace HDF5.Extension
{
    using System;

    using HDF.PInvoke;

    using hid_t = System.Int64;
    using htri_t = System.Int32;

    public static partial class HDF5Helper
    {
        private static readonly hid_t[] NumericTypeToHDF5TypeMap = new hid_t[Enum.GetValues(typeof(TypeCode)).Length];

        public static hid_t NumericTypeToHDF5Type<T>()
        {
            return NumericTypeToHDF5Type(typeof(T));
        }

#if false
        public static hid_t NumericTypeToHDF5Type(Type type)
        {
            if (type == null)
                throw new ArgumentNullException("type");

            switch (Type.GetTypeCode(type))
            {
                case TypeCode.SByte:
                    return H5T.NATIVE_INT8;
                case TypeCode.Byte:
                    return H5T.NATIVE_UINT8;
                case TypeCode.Int16:
                    return H5T.NATIVE_INT16;
                case TypeCode.UInt16:
                    return H5T.NATIVE_UINT16;
                case TypeCode.Int32:
                    return H5T.NATIVE_INT32;
                case TypeCode.UInt32:
                    return H5T.NATIVE_UINT32;
                case TypeCode.Int64:
                    return H5T.NATIVE_INT64;
                case TypeCode.UInt64:
                    return H5T.NATIVE_UINT64;
                case TypeCode.Single:
                    return H5T.NATIVE_FLOAT;
                case TypeCode.Double:
                    return H5T.NATIVE_DOUBLE;
                default:
                    throw new NotImplementedException(string.Format("{0}", type));
            }
        }
#else
        public static hid_t NumericTypeToHDF5Type(Type type)
        {
            var typeCode = (int)Type.GetTypeCode(type);
            if (typeCode < 0 || typeCode >= NumericTypeToHDF5TypeMap.Length ||
                NumericTypeToHDF5TypeMap[typeCode] == -1)
                throw new NotImplementedException(string.Format("{0}", type));

            return NumericTypeToHDF5TypeMap[typeCode];
        }
#endif

        internal static bool htri_t_to_bool(htri_t result, string function)
        {
            if (result < 0)
                throw new HDF5Exception("{0} failed.", function);

            return result > 0;
        }
    }
}
