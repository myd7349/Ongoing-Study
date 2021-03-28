// A rewrite of https://gist.github.com/simleb/5205083 with HDF5's C++ APIs.
// clang-format off
#include <iostream>

#include <H5Cpp.h>
// clang-format on

// Constants
const char saveFilePath[] = "test.h5";
const hsize_t ndims = 2;
const hsize_t ncols = 3;

int main()
{
    // Create a hdf5 file
    H5::H5File file(saveFilePath, H5F_ACC_TRUNC);
    std::cout << "- File created" << std::endl;

    // Create a 2D dataspace
    // The size of the first dimension is unlimited (initially 0)
    // The size of the second dimension is fixed
    hsize_t dims[ndims] = {0, ncols};
    hsize_t max_dims[ndims] = {H5S_UNLIMITED, ncols};
    H5::DataSpace file_space(ndims, dims, max_dims);
    std::cout << "- Dataspace created" << std::endl;

    // Create a dataset creation property list
    // The layout of the dataset have to be chunked when using unlimited dimensions
    H5::DSetCreatPropList plist;
    plist.setLayout(H5D_CHUNKED);
    // The choice of the chunk size affects performances
    // This is a toy example so we will choose one line
    hsize_t chunk_dims[ndims] = {2, ncols};
    plist.setChunk(ndims, chunk_dims);
    std::cout << "- Property list created" << std::endl;

    // Create the dataset 'dset1'
    auto dset = file.createDataSet("dset1", H5T_NATIVE_FLOAT, file_space, plist);
    std::cout << "- Dataset 'dset1' created" << std::endl;

    // Close resources
    plist.close();
    file_space.close();
    // We don't need the file dataspace anymore because when the dataset will be extended,
    // we will have to grab the updated file dataspace anyway

    // We will now append two buffers to the end of the datset
    // The first one will be two lines long
    // The second one will be three lines long

    // ## First buffer

    // Create 2D buffer (contigous in memory, row major order)
    // We will allocate enough memory to store 3 lines, so we can reuse the buffer
    hsize_t nlines = 3;
    float *buffer = new float[nlines * ncols];
    // Let us create an array of pointers so we can use the b[i][j] notation
    // instead of buffer[i * ncols + j]
    float **b = new float*[nlines];
    for (hsize_t i = 0; i < nlines; ++i){
        b[i] = &buffer[i * ncols];
    }

    // Initial values in buffer to be written in the dataset
    b[0][0] = 0.1f;
    b[0][1] = 0.2f;
    b[0][2] = 0.3f;
    b[1][0] = 0.4f;
    b[1][1] = 0.5f;
    b[1][2] = 0.6f;

    // Create a memory dataspace to indicate the size of our buffer
    // Remember the first buffer is only two lines long
    dims[0] = 2;
    dims[1] = ncols;
    H5::DataSpace mem_space(ndims, dims);
    std::cout << "- Memory dataspace created" << std::endl;

    // Extend dataset
    // We set the initial size of the dataset to 0x3, we thus need to extend it first
    // Note that we extend the dataset itself, not its dataspace
    // Remember the first buffer is only two lines long
    dims[0] = 2;
    dims[1] = ncols;
    dset.extend(dims);
    std::cout << "- Dataset extended" << std::endl;

    // Select hyperslab on file dataset
    file_space = dset.getSpace();
    hsize_t start[2] = {0, 0};
    hsize_t count[2] = {2, ncols};
    file_space.selectHyperslab(H5S_SELECT_SET, count, start);
    std::cout << "- First hyperslab selected" << std::endl;

    // Write buffer to dataset
    // mem_space and file_space should now have the same number of elements selected
    // note that buffer and &b[0][0] are equivalent
    dset.write(buffer, H5T_NATIVE_FLOAT, mem_space, file_space);
    std::cout << "- First buffer written" << std::endl;
    
    // We can now close the file dataspace
    // We could close the memory dataspace and create a new one,
    // but we will simply update its size
    file_space.close();

    // ## Second buffer

    // New values in buffer to be appended to the dataset
    b[0][0] = 1.1f;
    b[0][1] = 1.2f;
    b[0][2] = 1.3f;
    b[1][0] = 1.4f;
    b[1][1] = 1.5f;
    b[1][2] = 1.6f;
    b[2][0] = 1.7f;
    b[2][1] = 1.8f;
    b[2][2] = 1.9f;

    // Resize the memory dataspace to indicate the new size of our buffer
    // The second buffer is three lines long
    dims[0] = 3;
    dims[1] = ncols;
    mem_space.setExtentSimple(ndims, dims);
    std::cout << "- Memory dataspace resized" << std::endl;

    // Extend dataset
    // Note that in this simple example, we know that 2 + 3 = 5
    // In general, you could read the current extent from the file dataspace
    // and add the desired number of lines to it
    dims[0] = 5;
    dims[1] = ncols;
    dset.extend(dims);
    std::cout << "- Dataset extended" << std::endl;

    // Select hyperslab on file dataset
    // Again in this simple example, we know that 0 + 2 = 2
    // In general, you could read the current extent from the file dataspace
    // The second buffer is three lines long
    file_space = dset.getSpace();
    start[0] = 2;
    start[1] = 0;
    count[0] = 3;
    count[1] = ncols;
    file_space.selectHyperslab(H5S_SELECT_SET, count, start);
    std::cout << "- Second hyperslab selected" << std::endl;

    // Append buffer to dataset
    dset.write(buffer, H5T_NATIVE_FLOAT, mem_space, file_space);
    std::cout << "- Second buffer written" << std::endl;

    // Close resources
    delete[] b;
    delete[] buffer;
    file_space.close();
    mem_space.close();
    dset.close();
    file.close();
    std::cout << "- Resources released" << std::endl;

    return 0;
}

// clang-format off
// References:
// [Chunking and Extendible Datasets](https://www.asc.ohio-state.edu/wilkins.5/computing/HDF/hdf5tutorial/extend.html)
// [Writing & Appending arrays of float to the only dataset in hdf5 file in C++](https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c)
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/h5tutr_extend.cpp
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/extend_ds.cpp
// https://github.com/HDFGroup/hdf5/blob/develop/examples/h5_extend.c
// https://github.com/HDFGroup/hdf5/blob/develop/examples/h5_extend_write.c
// [HDF5 C++ interface: writing dynamic 2D arrays](https://stackoverflow.com/questions/7412042/hdf5-c-interface-writing-dynamic-2d-arrays)
// [h5py - reshape dataset like numpy.reshape()](https://stackoverflow.com/questions/56190439/h5py-reshape-dataset-like-numpy-reshape)
// [How do I fill an n-dimensional array in HDF5 from a 1D source?](https://stackoverflow.com/questions/20007123/how-do-i-fill-an-n-dimensional-array-in-hdf5-from-a-1d-source)
// clang-format on
