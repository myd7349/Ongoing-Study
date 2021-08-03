namespace HDF5.Extension
{
    using System;

    using HDF.PInvoke;

    using Common;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool WriteAttribute(hid_t hid, string key, sbyte value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, byte value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t attribute, sbyte value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t attribute, byte value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, short value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, ushort value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t attribute, short value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t attribute, ushort value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, int value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, uint value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t attribute, int value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t attribute, uint value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, long value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, ulong value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t attribute, long value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t attribute, ulong value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, float value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t hid, string key, double value)
        {
            return WriteScalarNumericAttribute(hid, key, value);
        }

        public static bool WriteAttribute(hid_t attribute, float value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteAttribute(hid_t attribute, double value)
        {
            return WriteScalarNumericAttribute(attribute, value);
        }

        public static bool WriteScalarNumericAttribute<T>(hid_t hid, string key, T value, hid_t type) where T : struct
        {
            if (key == null)
                throw new ArgumentNullException("key");

            var exists = H5A.exists(hid, key);
            if (exists < 0)
                throw new Exception("H5A.exists failed");

            if (exists == 0)
            {
                var space = H5S.create(H5S.class_t.SCALAR);
                if (space < 0)
                    throw new Exception("Failed to create scalar space");

                var attribute = H5A.create(hid, key, type, space);
                if (attribute < 0)
                {
                    H5S.close(space);
                    throw new Exception(string.Format("Failed to create attribute \"{0}\"", key));
                }

                H5S.close(space);

                object boxedValue = value;
                H5A.write(attribute, type, new PinnedObject(boxedValue));

                H5A.close(attribute);

                return true;
            }
            else
            {
                var attribute = H5A.open(hid, key);
                if (attribute < 0)
                    throw new Exception(string.Format("Failed to open attribute \"{0}\"", key));

                try
                {
                    return WriteScalarNumericAttribute(attribute, value, type);
                }
                finally
                {
                    H5A.close(attribute);
                }
            }
        }

        public static bool WriteScalarNumericAttribute<T>(hid_t hid, string key, T value) where T : struct
        {
            return WriteScalarNumericAttribute(hid, key, value, NumericTypeToHDF5Type<T>());
        }

        public static bool WriteScalarNumericAttribute<T>(hid_t attribute, T value, hid_t type) where T : struct
        {
            var space = H5A.get_space(attribute);
            if (space < 0)
                throw new Exception("Failed to get space");

            if (H5S.get_simple_extent_type(space) != H5S.class_t.SCALAR)
            {
                H5S.close(space);
                throw new Exception("Not a scalar data space");
            }

            H5S.close(space);

            var attributeType = H5A.get_type(attribute);
            if (attributeType < 0)
                throw new Exception("Failed to get type");

            var attributeTypeClass = H5T.get_class(attributeType);
            H5T.close(attributeType);
            if (attributeTypeClass != H5T.class_t.INTEGER && attributeTypeClass != H5T.class_t.FLOAT)
                throw new Exception("Not an integral or floating point data type");

            // TODO:
            // Check if value can be cast to type of this attribute.
            object boxedValue = value;
            H5A.write(attribute, type, new PinnedObject(boxedValue));

            return true;
        }

        public static bool WriteScalarNumericAttribute<T>(hid_t attribute, T value) where T : struct
        {
            return WriteScalarNumericAttribute(attribute, value, NumericTypeToHDF5Type<T>());
        }

        public static T ReadScalarNumericAttribute<T>(hid_t hid, string key) where T : struct
        {
            if (key == null)
                throw new ArgumentNullException("key");

            var attribute = H5A.open(hid, key);
            if (attribute < 0)
                throw new Exception(string.Format("Failed to open attribute \"{0}\"", key));

            try
            {
                return ReadScalarNumericAttribute<T>(attribute);
            }
            finally
            {
                H5A.close(attribute);
            }
        }

        public static T ReadScalarNumericAttribute<T>(hid_t attribute) where T : struct
        {
            var space = H5A.get_space(attribute);
            if (space < 0)
                throw new Exception("Failed to get space");

            if (H5S.get_simple_extent_type(space) != H5S.class_t.SCALAR)
            {
                H5S.close(space);
                throw new Exception("Not a scalar data space");
            }

            H5S.close(space);

            var type = H5A.get_type(attribute);
            if (type < 0)
                throw new Exception("Failed to get type");

            var typeClass = H5T.get_class(type);
            H5T.close(type);
            if (typeClass != H5T.class_t.INTEGER && typeClass != H5T.class_t.FLOAT)
                throw new Exception("Not an integral or floating point data type");

            // TODO:
            // Check if value can be cast to type of this attribute.
            //
            // TODO:
            // T[] value = new T[1];
            // H5A.read(attribute, NumericTypeToHDF5Type<T>(), new PinnedObject(value));
            object boxedValue = new T();
            if (H5A.read(attribute, NumericTypeToHDF5Type<T>(), new PinnedObject(boxedValue)) < 0)
                throw new Exception("Failed to read attribute");

            return (T)boxedValue;
        }
    }
}

// References:
// [How to use Switch…Case in generic type parameter in C#?](https://stackoverflow.com/questions/49758462/how-to-use-switch-case-in-generic-type-parameter-in-c)
// [Check if String can be converted to a given type in C#](Check if String can be converted to a given type in C# [duplicate])
// [Compare two Types](https://stackoverflow.com/questions/4875515/compare-two-types)
