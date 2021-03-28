// https://gist.github.com/simleb/5205083
// clang-format off
#include <stdio.h>
#include <stdlib.h>

#include <hdf5.h>
// clang-format on

// Constants
const char saveFilePath[] = "test.h5";

#define ndims (2)
#define ncols (3)


int main(void)
{
    // Create a hdf5 file
    hid_t file = H5Fcreate(saveFilePath, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    puts("- File created");

    // Create a 2D dataspace
    // The size of the first dimension is unlimited (initially 0)
    // The size of the second dimension is fixed
    hsize_t dims[ndims] = {0, ncols};
    hsize_t max_dims[ndims] = {H5S_UNLIMITED, ncols};
    hid_t file_space = H5Screate_simple(ndims, dims, max_dims);
    puts("- Dataspace created");

    // Create a dataset creation property list
    // The layout of the dataset have to be chunked when using unlimited dimensions
    hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(plist, H5D_CHUNKED);
    // The choice of the chunk size affects performances
    // This is a toy example so we will choose one line
    hsize_t chunk_dims[ndims] = {2, ncols};
    H5Pset_chunk(plist, ndims, chunk_dims);
    puts("- Property list created");

    // Create the dataset 'dset1'
    hid_t dset = H5Dcreate(file, "dset1", H5T_NATIVE_FLOAT, file_space, H5P_DEFAULT, plist, H5P_DEFAULT);
    puts("- Dataset 'dset1' created");

    // Close resources
    H5Pclose(plist);
    H5Sclose(file_space);
    // We don't need the file dataspace anymore because when the dataset will be extended,
    // we will have to grab the updated file dataspace anyway

    // We will now append two buffers to the end of the datset
    // The first one will be two lines long
    // The second one will be three lines long

    // ## First buffer

    // Create 2D buffer (contigous in memory, row major order)
    // We will allocate enough memory to store 3 lines, so we can reuse the buffer
    hsize_t nlines = 3;
    float *buffer = malloc(nlines * ncols * sizeof(float));
    // Let us create an array of pointers so we can use the b[i][j] notation
    // instead of buffer[i * ncols + j]
    float **b = malloc(nlines * sizeof(float *));
    for (hsize_t i = 0; i < nlines; ++i){
        b[i] = &buffer[i * ncols];
    }

    // Initial values in buffer to be written in the dataset
    b[0][0] = 0.1;
    b[0][1] = 0.2;
    b[0][2] = 0.3;
    b[1][0] = 0.4;
    b[1][1] = 0.5;
    b[1][2] = 0.6;

    // Create a memory dataspace to indicate the size of our buffer
    // Remember the first buffer is only two lines long
    dims[0] = 2;
    dims[1] = ncols;
    hid_t mem_space = H5Screate_simple(ndims, dims, NULL);
    puts("- Memory dataspace created");

    // Extend dataset
    // We set the initial size of the dataset to 0x3, we thus need to extend it first
    // Note that we extend the dataset itself, not its dataspace
    // Remember the first buffer is only two lines long
    dims[0] = 2;
    dims[1] = ncols;
    H5Dset_extent(dset, dims);
    puts("- Dataset extended");

    // Select hyperslab on file dataset
    file_space = H5Dget_space(dset);
    hsize_t start[2] = {0, 0};
    hsize_t count[2] = {2, ncols};
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET, start, NULL, count, NULL);
    puts("- First hyperslab selected");

    // Write buffer to dataset
    // mem_space and file_space should now have the same number of elements selected
    // note that buffer and &b[0][0] are equivalent
    H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT, buffer);
    puts("- First buffer written");
    
    // We can now close the file dataspace
    // We could close the memory dataspace and create a new one,
    // but we will simply update its size
    H5Sclose(file_space);

    // ## Second buffer

    // New values in buffer to be appended to the dataset
    b[0][0] = 1.1;
    b[0][1] = 1.2;
    b[0][2] = 1.3;
    b[1][0] = 1.4;
    b[1][1] = 1.5;
    b[1][2] = 1.6;
    b[2][0] = 1.7;
    b[2][1] = 1.8;
    b[2][2] = 1.9;

    // Resize the memory dataspace to indicate the new size of our buffer
    // The second buffer is three lines long
    dims[0] = 3;
    dims[1] = ncols;
    H5Sset_extent_simple(mem_space, ndims, dims, NULL);
    puts("- Memory dataspace resized");

    // Extend dataset
    // Note that in this simple example, we know that 2 + 3 = 5
    // In general, you could read the current extent from the file dataspace
    // and add the desired number of lines to it
    dims[0] = 5;
    dims[1] = ncols;
    H5Dset_extent(dset, dims);
    puts("- Dataset extended");

    // Select hyperslab on file dataset
    // Again in this simple example, we know that 0 + 2 = 2
    // In general, you could read the current extent from the file dataspace
    // The second buffer is three lines long
    file_space = H5Dget_space(dset);
    start[0] = 2;
    start[1] = 0;
    count[0] = 3;
    count[1] = ncols;
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET, start, NULL, count, NULL);
    puts("- Second hyperslab selected");

    // Append buffer to dataset
    H5Dwrite(dset, H5T_NATIVE_FLOAT, mem_space, file_space, H5P_DEFAULT, buffer);
    puts("- Second buffer written");

    // Close resources
    free(b);
    free(buffer);
    H5Sclose(file_space);
    H5Sclose(mem_space);
    H5Dclose(dset);
    H5Fclose(file);
    puts("- Resources released");

    return 0;
}

// clang-format off
// References:
// [Writing & Appending arrays of float to the only dataset in hdf5 file in C++](https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c)
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm
// clang-format on
