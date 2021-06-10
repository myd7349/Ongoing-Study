#include <hdf5.h>

int main(void)
{
    hid_t file = H5Fcreate("a.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    hsize_t dims[2] = { 0, 2 };
    hsize_t max_dims[2] = { H5S_UNLIMITED, 2 };
    hid_t file_space = H5Screate_simple(2, dims, max_dims);

    hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(plist, H5D_CHUNKED);
    hsize_t chunk_dims[2] = { 2, 2 };
    H5Pset_chunk(plist, 2, chunk_dims);

    hid_t dset = H5Dcreate(file, "dset1", H5T_NATIVE_FLOAT, file_space, H5P_DEFAULT, plist, H5P_DEFAULT);

    H5Pclose(plist);
    H5Sclose(file_space);

    float data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

    dims[0] = 3;
    dims[1] = 2;
    hid_t mem_space = H5Screate_simple(2, dims, NULL);

    dims[0] = 3;
    dims[1] = 2;
    H5Dset_extent(dset, dims);

    file_space = H5Dget_space(dset);
    hsize_t start[2] = { 0, 0 };
    hsize_t count[2] = { 3, 2 };
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET, start, NULL, count, NULL);

    H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT, data);

    H5Sclose(file_space);
    H5Sclose(mem_space);
    H5Dclose(dset);
    H5Fclose(file);

    return 0;
}
