namespace HDF5.Extension
{
    using System;
    using System.Linq;

    using HDF.PInvoke;

    using Common;

    using hid_t = System.Int64;
    using System.Runtime.InteropServices;

    internal enum Boolean : byte
    {
        FALSE = 0,
        TRUE = 1
    }

    public static partial class HDF5Helper
    {
        public static bool WriteAttribute(hid_t hid, string key, bool value)
        {
            return WriteEnumAttribute<Boolean>(hid, key, value ? Boolean.TRUE : Boolean.FALSE);
        }

        public static bool WriteEnumAttribute<T>(hid_t hid, string key, T value) where T : struct, IConvertible
        {
            var enumSize = EnumHelper.GetUnderlyingTypeSize<T>();

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

                var unmanagedBuffer = new UnmanagedBuffer(enumSize);
                unmanagedBuffer.WriteEnum(value);
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

                var unmanagedBuffer = new UnmanagedBuffer(enumSize);
                unmanagedBuffer.WriteEnum(value);

                H5A.write(attribute, type, unmanagedBuffer);

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

            return unmanagedBuffer.ReadEnum<T>();
        }

        public static hid_t CreateEnumType<T>(string[] names, T[] values)
        {
            if (names == null)
                throw new ArgumentNullException("names");

            if (values == null)
                throw new ArgumentNullException("values");

            if (names.Length == 0)
                throw new ArgumentException("names");

            if (values.Length == 0)
                throw new ArgumentException("values");

            if (names.Length != values.Length)
                throw new ArgumentException("names.Length != values.Length");

            if (names.Any(string.IsNullOrEmpty))
                throw new ArgumentException("names");

            if (names.Distinct().Count() != names.Length)
                throw new ArgumentException("duplicate in names");

            if (values.Distinct().Count() != values.Length)
                throw new ArgumentException("duplicate in values");

            var type = typeof(T);

            var size = 0;
            if (type.IsEnum)
                size = EnumHelper.GetUnderlyingTypeSize<T>();
            else
                size = Marshal.SizeOf(type);

            var enumType = H5T.create(H5T.class_t.ENUM, new IntPtr(size));
            if (enumType < 0)
                throw new HDF5Exception("Failed to create enum type");

            for (int i = 0; i < values.Length; ++i)
            {
                var value = values[i];

                var unmanagedBuffer = new UnmanagedBuffer(size);
                if (type.IsEnum)
                    unmanagedBuffer.WriteEnum(value);
                else
                    unmanagedBuffer.Write(value);

                // TODO: Should I call H5T.convert before H5T.enum_insert?
                if (H5T.enum_insert(enumType, names[i], unmanagedBuffer) < 0)
                {
                    H5T.close(enumType);
                    throw new HDF5Exception("Failed to insert enum: {0} = {1}", names[i], value);
                }
            }

            return enumType;
        }

        public static hid_t CreateEnumType<T>()
        {
            var size = EnumHelper.GetUnderlyingTypeSize<T>();
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

                var unmanagedBuffer = new UnmanagedBuffer(size);
                unmanagedBuffer.WriteEnum(value);

                // TODO: Should I call H5T.convert before H5T.enum_insert?
                if (H5T.enum_insert(enumType, Enum.GetName(type, value), unmanagedBuffer) < 0)
                {
                    H5T.close(enumType);
                    return -1;
                }
            }

            return enumType;
        }
    }
}


// References:
// [7. Enumeration Data Types](https://support.hdfgroup.org/HDF5/doc/H5.user/DatatypesEnum.html)
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_14/C/H5T/h5ex_t_enum.c
// https://support.hdfgroup.org/HDF5/doc/H5.user/DatatypesEnum.html
// [C# Determine Duplicate in List](https://stackoverflow.com/questions/5080538/c-sharp-determine-duplicate-in-list)
