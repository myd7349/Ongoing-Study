namespace HDF5.Extension
{
    using System;

    using HDF.PInvoke;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool IsHdf5File(string filePath)
        {
            if (string.IsNullOrEmpty(filePath))
                throw new ArgumentException("filePath");

            return htri_t_to_bool(H5F.is_hdf5(filePath), "H5F.is_hdf5");
        }

        public static void FlushFile(hid_t file, bool global = true)
        {
            var scope = global ? H5F.scope_t.GLOBAL : H5F.scope_t.LOCAL;
            if (H5F.flush(file, scope) < 0)
                throw new HDF5Exception("Failed to flush file.");
        }
    }
}


// References:
// [Corrupt files when creating HDF5 files without closing them(h5py)](https://stackoverflow.com/questions/31287744/corrupt-files-when-creating-hdf5-files-without-closing-them-h5py)
// > It indeed helps to `flush()` after writing.Even if you write data afterwards that you didn't flush,  everything up to the point of the most recent flush is accessible. 
