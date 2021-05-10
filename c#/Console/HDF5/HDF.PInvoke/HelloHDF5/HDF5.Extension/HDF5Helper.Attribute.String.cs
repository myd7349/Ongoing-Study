namespace HDF5.Extension
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Runtime.InteropServices;
    using System.Text;

    using HDF.PInvoke;

    using Common;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool WriteAttribute(hid_t hid, string key, string value, bool utf8 = true, bool variable = true)
        {
            var exists = H5A.exists(hid, key);
            if (exists < 0)
                throw new Exception("H5A.exists failed");

            if (exists == 0)
            {
                // Attribute doesn't exist.
                return variable ? WriteVariableStringAttribute(hid, key, new string[] { value }, utf8)
                    : WriteFixedStringAttribute(hid, key, value, utf8);
            }
            else
            {
                var attribute = H5A.open(hid, key);
                if (attribute < 0)
                    throw new Exception(string.Format("Failed to open attribute \"{0}\"", key));

                var type = H5A.get_type(attribute);
                if (type < 0)
                {
                    H5A.close(attribute);
                    return false;
                }

                var typeClass = H5T.get_class(type);
                if (typeClass == H5T.class_t.NO_CLASS)
                {
                    H5T.close(type);
                    H5A.close(attribute);
                    return false;
                }

                if (typeClass != H5T.class_t.STRING)
                {
                    H5T.close(type);
                    H5A.close(attribute);
                    throw new ArgumentException("H5T.get_class(type) != H5T.class_t.STRING");
                }

                utf8 = H5T.get_cset(type) == H5T.cset_t.UTF8;

                bool ok;
                if (H5T.is_variable_str(type) > 0)
                    ok = WriteVariableStringAttribute(hid, key, new string[] { value }, utf8);
                else
                    ok = WriteFixedStringAttribute(hid, key, value, utf8);

                H5T.close(type);
                H5A.close(attribute);

                return ok;
            }
        }

        public static bool WriteFixedStringAttribute(hid_t hid, string key, string value, bool utf8)
        {
            var exists = H5A.exists(hid, key);
            if (exists < 0)
                throw new Exception("H5A.exists failed");

            if (exists == 0) // Attribute doesn't exist
            {
                var bytes = value.ToBytes(utf8);

                var type = CreateFixedStringType(bytes, utf8);

                var space = H5S.create(H5S.class_t.SCALAR);
                if (space < 0)
                {
                    H5T.close(type);
                    throw new Exception("Failed to create scalar space");
                }

                var attribute = H5A.create(hid, key, type, space);
                if (attribute < 0)
                {
                    H5S.close(space);
                    H5T.close(type);
                    throw new Exception(string.Format("Failed to create attribute \"{0}\"", key));
                }

                H5A.write(attribute, type, new PinnedObject(bytes));

                H5A.close(attribute);
                H5S.close(space);
                H5T.close(type);

                return true;
            }
            else
            {
                var attribute = H5A.open(hid, key);
                if (attribute < 0)
                    throw new Exception(string.Format("Failed to open attribute \"{0}\"", key));

                try
                {
                    return WriteFixedStringAttribute(attribute, value, utf8);
                }
                finally
                {
                    H5A.close(attribute);
                }
            }
        }

        public static bool WriteFixedStringAttribute(hid_t attribute, string value, bool utf8)
        {
            if (value == null)
                throw new ArgumentNullException("value");

            var space = H5A.get_space(attribute);
            if (space < 0)
                throw new Exception("Failed to get data space");

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
            if (typeClass != H5T.class_t.STRING)
            {
                H5T.close(type);
                throw new Exception("Not a string attribute");
            }

            var isVariableString = H5T.is_variable_str(type);
            H5T.close(type);
            if (isVariableString < 0)
                throw new Exception("H5T.is_variable_str failed");

            if (isVariableString > 0)
                throw new Exception("Not a fixed string attribute");

            // TODO: Do we really need to create a new memory type here?
            var bytes = value.ToBytes(utf8);

            var memType = CreateFixedStringType(bytes, utf8);

            // TODO: type or memType here?
            H5A.write(attribute, memType, new PinnedObject(bytes));

            H5T.close(memType);

            return true;
        }

        public static bool WriteVariableStringAttribute(hid_t hid, string key, string value, bool utf8)
        {
            if (value == null)
                throw new ArgumentNullException("value");

            return WriteVariableStringAttribute(hid, key, new string[] { value }, utf8);
        }

        public static bool WriteVariableStringAttribute(hid_t hid, string key, IEnumerable<string> values, bool utf8)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            if (values == null)
                throw new ArgumentNullException("values");

            var exists = H5A.exists(hid, key);
            if (exists < 0)
                throw new Exception("H5A.exists failed");

            if (exists == 0) // Attribute doesn't exist
            {
#if true
                var type = H5T.create(H5T.class_t.STRING, H5T.VARIABLE);
                if (type < 0)
                    throw new Exception("Failed to create string type");
#else
                var type = H5T.copy(H5T.C_S1);
                if (type < 0)
                    throw new Exception("Failed to create string type");

                if (H5T.set_size(type, H5T.VARIABLE) < 0)
                {
                    H5T.close(type);
                    throw new Exception("Failed to set type size");
                }
#endif

                if (utf8)
                {
                    if (H5T.set_cset(type, H5T.cset_t.UTF8) < 0)
                    {
                        H5T.close(type);
                        throw new Exception("Failed to set cset");
                    }
                }

                if (H5T.set_strpad(type, H5T.str_t.NULLTERM) < 0)
                {
                    H5T.close(type);
                    throw new Exception("Failed to set strpad");
                }

                var space = values.Count() == 1 ? H5S.create(H5S.class_t.SCALAR)
                    : H5S.create_simple(1, new ulong[1] { (ulong)values.Count() }, null);
                if (space < 0)
                {
                    H5T.close(type);
                    throw new Exception("Failed to create data space");
                }

                var attribute = H5A.create(hid, key, type, space);
                H5S.close(space);
                if (attribute < 0)
                {
                    H5T.close(type);
                    throw new Exception(string.Format("Failed to create attribute \"{0}\"", key));
                }

                var pinnedObjects = new PinnedObject[values.Count()];
                var data = new IntPtr[values.Count()];
                int count = 0;
                foreach (string str in values)
                {
                    var bytes = str.ToBytes(utf8);
                    pinnedObjects[count] = new PinnedObject(bytes);
                    data[count] = pinnedObjects[count];
                    count += 1;
                }

                H5A.write(attribute, type, new PinnedObject(data));

                H5T.close(type);
                H5A.close(attribute);
            }
            else
            {
                // Attribute exists.
                var attribute = H5A.open(hid, key);
                if (attribute < 0)
                    throw new Exception(string.Format("Failed to open attribute \"{0}\"", key));

                var type = H5A.get_type(attribute);
                if (type < 0)
                {
                    H5A.close(attribute);
                    throw new Exception("Failed to get data type");
                }

                var pinnedObjects = new PinnedObject[values.Count()];
                var data = new IntPtr[values.Count()];
                int count = 0;
                foreach (string str in values)
                {
                    var bytes = str.ToBytes(utf8);
                    pinnedObjects[count] = new PinnedObject(bytes);
                    data[count] = pinnedObjects[count];
                    count += 1;
                }

                H5A.write(attribute, type, new PinnedObject(data));

                H5T.close(type);
                H5A.close(attribute);
            }

            return true;
        }

        public static string ReadStringAttribute(hid_t hid, string key)
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

            var typeClass = H5T.get_class(type);
            if (typeClass != H5T.class_t.STRING)
            {
                H5T.close(type);
                throw new Exception("Not a string attribute");
            }

            var utf8 = H5T.get_cset(type) == H5T.cset_t.UTF8;
            var ascii = H5T.get_cset(type) == H5T.cset_t.ASCII;

            if (!utf8 && !ascii)
            {
                H5T.close(type);
                H5A.close(attribute);
                throw new Exception("Neither ASCII nor UTF8.");
            }

            var isVariableString = H5T.is_variable_str(type);
            if (isVariableString < 0)
            {
                H5T.close(type);
                H5A.close(attribute);
                throw new Exception("H5T.is_variable_str failed");
            }

            if (isVariableString > 0)
            {
                var space = H5A.get_space(attribute);
                if (space < 0)
                {
                    H5T.close(type);
                    H5A.close(attribute);
                    throw new Exception("H5A.get_space failed.");
                }

                hid_t count = H5S.get_simple_extent_npoints(space);
                var rdata = new IntPtr[count];

                H5A.read(attribute, type, new PinnedObject(rdata));

                var attrStrings = new List<string>();
                for (int i = 0; i < rdata.Length; ++i)
                {
                    int attrLength = 0;
                    while (Marshal.ReadByte(rdata[i], attrLength) != 0)
                    {
                        ++attrLength;
                    }

                    byte[] buffer = new byte[attrLength];
                    Marshal.Copy(rdata[i], buffer, 0, buffer.Length);

                    string part = utf8 ? Encoding.UTF8.GetString(buffer)
                        : Encoding.ASCII.GetString(buffer);

                    attrStrings.Add(part);

                    H5.free_memory(rdata[i]);
                }

                H5S.close(space);
                H5T.close(type);
                H5A.close(attribute);

                return attrStrings[0];
            }

            // Must be a non-variable length string.
            var size = H5T.get_size(type).ToInt32();
            var unmanagedBuffer = new UnmanagedBuffer(size);

            int result = H5A.read(attribute, type, unmanagedBuffer);
            if (result < 0)
            {
                H5T.close(type);
                H5D.close(attribute);
                throw new IOException("Failed to read attribute.");
            }

            var bytes = new byte[size];
            unmanagedBuffer.CopyTo(bytes, 0, bytes.Length);

            H5T.close(type);
            H5A.close(attribute);

            var value = utf8 ? Encoding.UTF8.GetString(bytes)
                : Encoding.ASCII.GetString(bytes);

            return value.TrimEnd('\0');
        }

        private static byte[] ToBytes(this string str, bool utf8)
        {
            if (string.IsNullOrEmpty(str))
                return new byte[0];

            return utf8 ? Encoding.UTF8.GetBytes(str) : Encoding.ASCII.GetBytes(str);
        }

        private static hid_t CreateFixedStringType(byte[] bytes, bool utf8)
        {
#if true
            var type = H5T.create(H5T.class_t.STRING, new IntPtr(bytes.Length));
            if (type < 0)
                throw new Exception("Failed to create string type");
#else
            var type = H5T.copy(H5T.C_S1);
            if (type < 0)
                throw new Exception("Failed to create string type");

            // TODO: bytes.Length or bytes.Length + 1?
            if (H5T.set_size(type, new IntPtr(bytes.Length)) < 0)
            {
                H5T.close(type);
                throw new Exception("Failed to set type size");
            }
#endif

            if (utf8)
            {
                if (H5T.set_cset(type, H5T.cset_t.UTF8) < 0)
                {
                    H5T.close(type);
                    throw new Exception("Failed to set cset");
                }
            }

            if (H5T.set_strpad(type, H5T.str_t.NULLTERM) < 0)
            {
                H5T.close(type);
                throw new Exception("Failed to set strpad");
            }

            return type;
        }
    }
}


// References:
// [How to read HDF5 variable length string attributes in C# .NET](https://stackoverflow.com/questions/51978853/how-to-read-hdf5-variable-length-string-attributes-in-c-sharp-net)
// [How to read a unicode string from a hdf-5 file with c#](https://stackoverflow.com/questions/37832163/how-to-read-a-unicode-string-from-a-hdf-5-file-with-c-sharp)
// https://github.com/reyntjesr/Hdf5DotnetTools
// https://github.com/LiorBanai/HDF5-CSharp/blob/master/HDF5-CSharp/Hdf5Attributes.cs
// [How to write fixed length strings in HDF5?](https://stackoverflow.com/questions/29528674/how-to-write-fixed-length-strings-in-hdf5/29565641)
