1. https://github.com/HDFGroup/Tutorial

2. Sample data: https://github.com/BITalinoWorld/revolution-sample-data

3. How to copy all attributes from another dataset?

   [Function to clone HDF5 file via C++](https://stackoverflow.com/questions/35402861/function-to-clone-hdf5-file-via-c)

   [H5Ocopy](https://github.com/HDFGroup/hdf5/blob/develop/tools/src/h5copy/h5copy.c) - According to https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm, this function doesn't have a C++ wrapper yet.

4. What if we encountered a PC power off when I was writing data into an opened dataset?

   [Corrupt files when creating HDF5 files without closing them (h5py)](https://stackoverflow.com/questions/31287744/corrupt-files-when-creating-hdf5-files-without-closing-them-h5py)

   [Flushing files sometimes corrupts them](https://forum.hdfgroup.org/t/flushing-files-sometimes-corrupts-them/4958)

5. Alternative C++ wrapper libraries?
   - [HighFive](https://github.com/BlueBrain/HighFive)
     - [xtensor-io](https://github.com/xtensor-stack/xtensor-io) depends on this library.
   - [h5cpp](https://github.com/steven-varga/h5cpp) - [talk](http://lightning-talk.h5cpp.org/#/)
   - [h5cpp](https://github.com/ess-dmsc/h5cpp)
   - [HDFql](https://www.hdfql.com/)

6. Check if a dataset/group exists.

   - [Test group existence in hdf5/c++](https://stackoverflow.com/questions/35668056/test-group-existence-in-hdf5-c)

     > https://github.com/HDFGroup/hdf5/blob/1.12/master/c++/src/H5AbstractDs.cpp#L64-L102
     >
     > ```c++
     > H5T_class_t AbstractDs::getTypeClass() const
     > {
     >     // Gets the datatype used by this dataset or attribute.
     >     // p_get_type calls either H5Dget_type or H5Aget_type depending on
     >     // which object invokes getTypeClass
     >     hid_t datatype_id;
     >     try {
     >         datatype_id = p_get_type();  // returned value is already validated
     >     }
     >     catch (DataSetIException& E) {
     >         throw DataTypeIException("DataSet::getTypeClass", E.getDetailMsg());
     >     }
     >     catch (AttributeIException& E) {
     >         throw DataTypeIException("Attribute::getTypeClass", E.getDetailMsg());
     >     }
     > 
     >     // Gets the class of the datatype and validate it before returning
     >     H5T_class_t type_class = H5Tget_class(datatype_id);
     > 
     >     // Close temporary datatype_id
     >     herr_t ret_value = H5Tclose(datatype_id);
     >     if (ret_value < 0)
     >     {
     >         if (fromClass() == "DataSet")
     >             throw DataTypeIException("DataSet::getTypeClass", "H5Tclose failed");
     >         else if (fromClass() == "Attribute")
     >             throw DataTypeIException("Attribute::getTypeClass", "H5Tclose failed");
     >     }
     > 
     >     // Check on the returned type_class
     >     if (type_class == H5T_NO_CLASS)
     >     {
     >         if (fromClass() == "DataSet")
     >             throw DataTypeIException("DataSet::getTypeClass", "H5Tget_class returns H5T_NO_CLASS");
     >         else if (fromClass() == "Attribute")
     >             throw DataTypeIException("Attribute::getTypeClass", "H5Tget_class returns H5T_NO_CLASS");
     >     }
     >     return(type_class);
     > }
     > ```

   Another example:

   ```c#
   // https://github.com/LiorBanai/HDF5-CSharp/blob/40805dc11f97f37fe1edd33ff52ea11261f78010/HDF5-CSharp/Hdf5Utils.cs#L83-L94
   public static bool ItemExists(long groupId, string groupName, Hdf5ElementType type)
   {
       switch (type)
       {
           case Hdf5ElementType.Group:
           case Hdf5ElementType.Dataset:
               return H5L.exists(groupId, NormalizedName(groupName)) > 0;
           case Hdf5ElementType.Attribute:
               return H5A.exists(groupId, NormalizedName(groupName)) > 0;
           default:
               throw new ArgumentOutOfRangeException(nameof(type), type, null);
       }
   }
   
   // https://github.com/LiorBanai/HDF5-CSharp/blob/40805dc11f97f37fe1edd33ff52ea11261f78010/HDF5-CSharp/Hdf5Dataset.cs#L42
   public static bool DatasetExists(long groupId, string datasetName) => Hdf5Utils.ItemExists(groupId, datasetName, Hdf5ElementType.Dataset);
   ```

7. H5::DataSet::extend will invalidate a data space

   - [HDF5: How to append data to a dataset (extensible array)](https://stackoverflow.com/questions/23934724/hdf5-how-to-append-data-to-a-dataset-extensible-array)

     > The problem is that after calling `H5Sget_simple_extent_dims` the dataspace id gets somehow invalidated and you need to get it again before reusing it.

   ```c++
   H5::H5File file(fileName, H5F_ACC_RDWR);
   H5::DataSet dataSet = file.openDataSet(dataSetName);
   
   H5::DataSpace fileSpace = dataSet.getSpace();
   
   if (fileSpace.getSimpleExtentNdims() != 2)
       return;
   
   hsize_t dims[2] = { 100, 100 };
   dataSet.extend(dims);
   
   // It is important!
   fileSpace.close();
   fileSpace = dataSet.getSpace();
   
   hsize_t offset[2] = { 0, 0 };
   hsize_t count[2] = { 100, 100 };
   
   short data[100][100] = { 0 };
   
   // Now, lets insert some data into dataSet.
   // ...
   fileSpace.selectHyperslab(H5S_SELECT_SET, count, offset);
   H5::DataSpace memSpace(2, count);
   dataSet.write(data, H5::PredType::NATIVE_INT16, memSpace, fileSpace);
   ```


6. [Build both release and debug](https://forum.hdfgroup.org/t/build-both-release-and-debug/5094) & [HDF5 - Visual Studio - Build in Release works, Debug fails](https://forum.hdfgroup.org/t/hdf5-visual-studio-build-in-release-works-debug-fails/878)

7. [Iterative recording of real-time data over long time periods](https://forum.hdfgroup.org/t/iterative-recording-of-real-time-data-over-long-time-periods/6985)

8. [how to read hdf5 boolean enum created by h5py in C](https://stackoverflow.com/questions/11627376/how-to-read-hdf5-boolean-enum-created-by-h5py-in-c)

9. zlib linking issue when built as a static library

   - [Unresolved external symbol with zlib and libpng. Visual studio 2013](https://stackoverflow.com/questions/37762981/unresolved-external-symbol-with-zlib-and-libpng-visual-studio-2013)

     > For fixing the unresolved symbols problem, open zlib project  preferences,  then go to Configuration Properties -> C/C++ -> Preprocessor, and  in the Preprocessor Definitions line remove “ZLIB_WINAPI;” (don’t forget to remove the trailing semicolon).

   - [Unresolved externals despite linking in zlib.lib](https://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib)