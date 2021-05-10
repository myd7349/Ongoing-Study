namespace HDF5.Extension
{
    using System;

    using HDF.PInvoke;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool GroupExists(hid_t hid, string groupName)
        {
            if (string.IsNullOrEmpty(groupName))
                throw new ArgumentException("groupName");

            var exists = H5L.exists(hid, groupName);
            if (exists < 0)
                throw new HDF5Exception("H5L.exists failed");

            if (exists == 0)
                return false;

            var objectId = H5O.open(hid, groupName);
            if (objectId < 0)
                throw new HDF5Exception("H5O.open failed");

            var result = GroupExists(objectId);

            H5O.close(objectId);

            return result;
        }

        public static bool GroupExists(hid_t group)
        {
            return H5I.get_type(group) == H5I.type_t.GROUP;
        }
    }
}
