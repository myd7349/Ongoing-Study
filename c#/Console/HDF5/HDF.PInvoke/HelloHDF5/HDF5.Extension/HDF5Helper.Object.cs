namespace HDF5.Extension
{
    using System;
    using System.Collections.Generic;
    using System.Runtime.InteropServices;
    using HDF.PInvoke;

    using hid_t = System.Int64;

    // TODO:
    // What is the difference between H5O.type_t and H5I.type_t?
    public static partial class HDF5Helper
    {
        public static Dictionary<H5O.type_t, List<string>> IterateObject(hid_t hid)
        {
            var objects = new Dictionary<H5O.type_t, List<string>>();

            H5O.visit(hid, H5.index_t.NAME, H5.iter_order_t.INC,
                new H5O.iterate_t(
                    delegate (hid_t objectId, IntPtr namePtr, ref H5O.info_t info, IntPtr data)
                    {
                        var objectName = Marshal.PtrToStringAnsi(namePtr);

                        switch (info.type)
                        {
                            case H5O.type_t.GROUP:
                                if (!objects.ContainsKey(H5O.type_t.GROUP))
                                    objects[H5O.type_t.GROUP] = new List<string>();
                                objects[H5O.type_t.GROUP].Add(objectName);
                                break;
                            case H5O.type_t.DATASET:
                                if (!objects.ContainsKey(H5O.type_t.DATASET))
                                    objects[H5O.type_t.DATASET] = new List<string>();
                                objects[H5O.type_t.DATASET].Add(objectName);
                                break;
                            case H5O.type_t.NAMED_DATATYPE:
                                if (!objects.ContainsKey(H5O.type_t.NAMED_DATATYPE))
                                    objects[H5O.type_t.NAMED_DATATYPE] = new List<string>();
                                objects[H5O.type_t.NAMED_DATATYPE].Add(objectName);
                                break;
                            default:
                                break;
                        }

                        return 0;
                    }), IntPtr.Zero);

            return objects;
        }

        public static Dictionary<H5I.type_t, List<string>> IterateObject2(hid_t hid)
        {
            var objects = new Dictionary<H5I.type_t, List<string>>();

            H5O.visit(hid, H5.index_t.NAME, H5.iter_order_t.INC,
                new H5O.iterate_t(
                    delegate (hid_t objectId, IntPtr namePtr, ref H5O.info_t info, IntPtr data)
                    {
                        var objectName = Marshal.PtrToStringAnsi(namePtr);

                        switch (H5I.get_type(objectId))
                        {
                            case H5I.type_t.GROUP:
                                if (!objects.ContainsKey(H5I.type_t.GROUP))
                                    objects[H5I.type_t.GROUP] = new List<string>();
                                objects[H5I.type_t.GROUP].Add(objectName);
                                break;
                            case H5I.type_t.DATASET:
                                if (!objects.ContainsKey(H5I.type_t.DATASET))
                                    objects[H5I.type_t.DATASET] = new List<string>();
                                objects[H5I.type_t.DATASET].Add(objectName);
                                break;
                            case H5I.type_t.DATATYPE:
                                if (!objects.ContainsKey(H5I.type_t.DATATYPE))
                                    objects[H5I.type_t.DATATYPE] = new List<string>();
                                objects[H5I.type_t.DATATYPE].Add(objectName);
                                break;
                            case H5I.type_t.ATTR:
                                if (!objects.ContainsKey(H5I.type_t.ATTR))
                                    objects[H5I.type_t.ATTR] = new List<string>();
                                objects[H5I.type_t.ATTR].Add(objectName);
                                break;
                            default:
                                break;
                        }

                        return 0;
                    }), IntPtr.Zero);

            return objects;
        }
    }
}


// References:
// [Cookbook: Iteration](https://github.com/HDFGroup/HDF.PInvoke/wiki/Cookbook-:-Iteration)
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_6/C/H5G/h5ex_g_iterate.c
