namespace HDF5.Extension
{
    using HDF.PInvoke;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static int GetDataSpaceRank(hid_t space)
        {
            var rank = H5S.get_simple_extent_ndims(space);
            if (rank < 0)
                throw new HDF5Exception("Failed to get rank of data set.");

            return rank;
        }

        public static void GetDataSpaceDimensions(hid_t space, ref ulong[] dims, ref ulong[] maxDims)
        {
            var rank = GetDataSpaceRank(space);

            dims = new ulong[rank];
            maxDims = new ulong[rank];

            if (H5S.get_simple_extent_dims(space, dims, maxDims) < 0)
            {
                dims = maxDims = null;
                throw new HDF5Exception("Failed to get dimensions of data set.");
            }
        }
    }
}
