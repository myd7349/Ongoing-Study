namespace HDF5.Extension
{
    using System;
    using System.Linq;
    using System.Runtime.InteropServices;

    using HDF.PInvoke;

    using Common;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool WriteEnumAttribute<T>(hid_t hid, string key, T value) where T : struct, IConvertible
        {
            var enumSize = GetEnumTypeSize<T>();

            if (!Enum.IsDefined(typeof(T), value))
                throw new ArgumentException("value");

            if (H5A.exists(hid, key) == 0)
            {
                // Attribute doesn't exist.
                var type = CreateEnumType<T>();
                if (type < 0)
                    return false;

                var space = H5S.create(H5S.class_t.SCALAR);
                if (space < 0)
                {
                    H5T.close(type);
                    return false;
                }

                var attribute = H5A.create(hid, key, type, space);
                if (attribute < 0)
                {
                    H5S.close(space);
                    H5T.close(type);
                    return false;
                }

                var unmanagedBuffer = WriteEnumToUnmanagedBuffer(value);
                H5A.write(attribute, type, unmanagedBuffer);

                H5A.close(attribute);
                H5S.close(space);
                H5T.close(type);
            }
            else
            {
                var attribute = H5A.open(hid, key);
                if (attribute < 0)
                    return false;

                var type = H5A.get_type(attribute);
                if (type < 0)
                {
                    H5A.close(attribute);
                    return false;
                }

                H5A.write(attribute, type, WriteEnumToUnmanagedBuffer(value));

                H5T.close(type);
                H5A.close(attribute);
            }

            return true;
        }

        public static T ReadEnumAttribute<T>(hid_t hid, string key) where T : struct, IConvertible
        {
            var attribute = H5A.open(hid, key);
            if (attribute < 0)
                throw new ArgumentException(string.Format("Attribute {0} not found.", key));

            var type = H5A.get_type(attribute);
            if (type < 0)
            {
                H5A.close(attribute);
                throw new Exception("H5A.get_type failed.");
            }

            var size = H5T.get_size(type).ToInt32();
            if (size == 0)
            {
                H5T.close(type);
                H5A.close(attribute);
                throw new Exception("H5T.get_size failed.");
            }

            var unmanagedBuffer = new UnmanagedBuffer(size);
            H5A.read(attribute, type, unmanagedBuffer);

            H5T.close(type);
            H5A.close(attribute);

            return ReadEnumFromUnmanagedBuffer<T>(unmanagedBuffer);
        }

        private static int GetEnumTypeSize<T>()
        {
            var type = typeof(T);
            if (!type.IsEnum)
                throw new ArgumentException("Not an enum type.");

            return Marshal.SizeOf(Enum.GetUnderlyingType(type));
        }

        private static hid_t CreateEnumType<T>()
        {
            var size = GetEnumTypeSize<T>();
            if (size != 1 && size != 2 && size != 4 && size != 8)
                throw new ArgumentException("Unexpected enum type size.");

            var enumType = H5T.create(H5T.class_t.ENUM, new IntPtr(size));
            if (enumType < 0)
                return -1;

            var type = typeof(T);

            // The mapping from symbols to integers is N:1 in C but 1:1 in HDF.
            // Consider:
            // enum MyEnum
            // {
            //     Foo = 0,
            //     Bar = Foo,
            // }
            var values = Enum.GetValues(type).OfType<T>().Distinct().ToArray();
            for (int i = 0; i < values.Length; ++i)
            {
                var value = values[i];
                var unmanagedBuffer = WriteEnumToUnmanagedBuffer<T>(value);
                // TODO: Should I call H5T.convert before H5T.enum_insert?
                if (H5T.enum_insert(enumType, Enum.GetName(type, value), unmanagedBuffer) < 0)
                {
                    H5T.close(enumType);
                    return -1;
                }
            }

            return enumType;
        }

        private static UnmanagedBuffer WriteEnumToUnmanagedBuffer<T>(T value)
        {
            var size = GetEnumTypeSize<T>();
            var unmanagedBuffer = new UnmanagedBuffer(size);

            var underlyingType = Enum.GetUnderlyingType(typeof(T));

            switch (size)
            {
                case 1:
                    if (underlyingType == typeof(byte))
                        Marshal.WriteByte(unmanagedBuffer, Convert.ToByte(value));
                    else
                        MarshalHelper.WriteSByte(unmanagedBuffer, Convert.ToSByte(value));
                    break;
                case 2:
                    if (underlyingType == typeof(short))
                        Marshal.WriteInt16(unmanagedBuffer, Convert.ToInt16(value));
                    else
                        MarshalHelper.WriteUInt16(unmanagedBuffer, Convert.ToUInt16(value));
                    break;
                case 4:
                    if (underlyingType == typeof(int))
                        Marshal.WriteInt32(unmanagedBuffer, Convert.ToInt32(value));
                    else
                        MarshalHelper.WriteUInt32(unmanagedBuffer, Convert.ToUInt32(value));
                    break;
                case 8:
                    if (underlyingType == typeof(long))
                        Marshal.WriteInt64(unmanagedBuffer, Convert.ToInt64(value));
                    else
                        MarshalHelper.WriteUInt64(unmanagedBuffer, Convert.ToUInt64(value));
                    break;
            }

            return unmanagedBuffer;
        }

        private static T ReadEnumFromUnmanagedBuffer<T>(UnmanagedBuffer unmanagedBuffer)
        {
            var size = GetEnumTypeSize<T>();

            var underlyingType = Enum.GetUnderlyingType(typeof(T));

            switch (size)
            {
                case 1:
                    if (underlyingType == typeof(byte))
                        return (T)(object)Marshal.ReadByte(unmanagedBuffer);
                    else
                        return (T)(object)MarshalHelper.ReadSByte(unmanagedBuffer);
                case 2:
                    if (underlyingType == typeof(short))
                        return (T)(object)Marshal.ReadInt16(unmanagedBuffer);
                    else
                        return (T)(object)MarshalHelper.ReadUInt16(unmanagedBuffer);
                case 4:
                    if (underlyingType == typeof(int))
                        return (T)(object)Marshal.ReadInt32(unmanagedBuffer);
                    else
                        return (T)(object)MarshalHelper.ReadUInt32(unmanagedBuffer);
                case 8:
                    if (underlyingType == typeof(long))
                        return (T)(object)Marshal.ReadInt64(unmanagedBuffer);
                    else
                        return (T)(object)MarshalHelper.ReadUInt64(unmanagedBuffer);
                default:
                    throw new Exception(string.Format("Unexpected enum size {0}.", size));
            }
        }
    }
}


// References:
// [7. Enumeration Data Types](https://support.hdfgroup.org/HDF5/doc/H5.user/DatatypesEnum.html)
// [Enum Size in Bytes](https://stackoverflow.com/questions/20944585/enum-size-in-bytes)
// [How do I cast a generic enum to int?](https://stackoverflow.com/questions/16960555/how-do-i-cast-a-generic-enum-to-int)
// [Cast Int to Generic Enum in C#](https://stackoverflow.com/questions/10387095/cast-int-to-generic-enum-in-c-sharp)
// [c# P/Invoke : Pass Enum value with IntPtr to Function; AccessViolationException](https://stackoverflow.com/questions/47723953/c-sharp-p-invoke-pass-enum-value-with-intptr-to-function-accessviolationexcep)
// [How to convert from System.Enum to base integer?](https://stackoverflow.com/questions/908543/how-to-convert-from-system-enum-to-base-integer)
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_14/C/H5T/h5ex_t_enum.c
// https://support.hdfgroup.org/HDF5/doc/H5.user/DatatypesEnum.html
// [How to find out if a numeric type is signed or unsigned in C#](https://stackoverflow.com/questions/53300136/how-to-find-out-if-a-numeric-type-is-signed-or-unsigned-in-c-sharp)
