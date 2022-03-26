1. https://github.com/HDFGroup/Tutorial

2. Sample data: https://github.com/BITalinoWorld/revolution-sample-data

3. How to copy all attributes from another dataset?
   
   [Function to clone HDF5 file via C++](https://stackoverflow.com/questions/35402861/function-to-clone-hdf5-file-via-c)
   
   [H5Ocopy](https://github.com/HDFGroup/hdf5/blob/develop/tools/src/h5copy/h5copy.c) - According to https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm, this function doesn't have a C++ wrapper yet.
   
   [h5copy](https://github.com/qsnake/hdf5/blob/master/tools/h5copy/h5copy.c)
   
   [H5copy; how to copy root ‘/’ attributes to target file?](https://forum.hdfgroup.org/t/h5copy-how-to-copy-root-attributes-to-target-file/7396)

4. What if we encountered a PC power off when I was writing data into an opened dataset?
   
   [Corrupt files when creating HDF5 files without closing them (h5py)](https://stackoverflow.com/questions/31287744/corrupt-files-when-creating-hdf5-files-without-closing-them-h5py)
   
   > It indeed helps to `flush()` after writing. Even if you write data afterwards that you didn't flush,  everything up to the point of the most recent flush is accessible. 
   
   [Flushing files sometimes corrupts them](https://forum.hdfgroup.org/t/flushing-files-sometimes-corrupts-them/4958)

5. Alternative C++ wrapper libraries?
   
   - [HighFive](https://github.com/BlueBrain/HighFive)
     - [xtensor-io](https://github.com/xtensor-stack/xtensor-io) depends on this library.
   - [h5cpp](https://github.com/steven-varga/h5cpp) - [talk](http://lightning-talk.h5cpp.org/#/)
   - [h5cpp](https://github.com/ess-dmsc/h5cpp)
   - [h5pp](https://github.com/DavidAce/h5pp)
   - [HDFql](https://www.hdfql.com/)
   - [openPMD-standard](https://github.com/openPMD/openPMD-standard)
   - [openPMD-api](https://github.com/openPMD/openPMD-api)
   - [hdf5serie](https://github.com/mbsim-env/hdf5serie)

6. Related projects
   
   - [libhio](https://github.com/hpc/libhio)
   - [gdl](https://github.com/gnudatalanguage/gdl)

7. Check if a dataset/group exists.
   
   H5Location::nameExists + IdComponent::getHDFObjType
   
   - [Test group existence in hdf5/c++](https://stackoverflow.com/questions/35668056/test-group-existence-in-hdf5-c)
   
   - https://support.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Exists
   
   - https://portal.hdfgroup.org/display/HDF5/H5L_EXISTS
     
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
   
   https://github.com/BlueBrain/HighFive/blob/2cd1f569945c87b085c459f9224705f13f51a091/include/highfive/bits/H5Object_misc.hpp#L59-L85
   
   > ```c++
   > static inline ObjectType _convert_object_type(const H5I_type_t& h5type) {
   >     switch (h5type) {
   >         case H5I_FILE:
   >             return ObjectType::File;
   >         case H5I_GROUP:
   >             return ObjectType::Group;
   >         case H5I_DATATYPE:
   >             return ObjectType::UserDataType;
   >         case H5I_DATASPACE:
   >             return ObjectType::DataSpace;
   >         case H5I_DATASET:
   >             return ObjectType::Dataset;
   >         case H5I_ATTR:
   >             return ObjectType::Attribute;
   >         default:
   >             return ObjectType::Other;
   >     }
   > }
   > 
   > inline ObjectType Object::getType() const {
   >     // H5Iget_type is a very lightweight func which extracts the type from the id
   >     H5I_type_t h5type;
   >     if ((h5type = H5Iget_type(_hid)) == H5I_BADID) {
   >         HDF5ErrMapper::ToException<ObjectException>("Invalid hid or object type");
   >     }
   >     return _convert_object_type(h5type);
   > }
   > ```
   
   [HDF5 Lite APIs](https://portal.hdfgroup.org/display/HDF5/Lite) include a function named [`H5LTfind_dataset`](https://portal.hdfgroup.org/display/HDF5/H5LT_FIND_DATASET)
   
   [h5ex_g_iterate.c](https://github.com/HDFGroup/hdf5-examples/blob/master/1_6/C/H5G/h5ex_g_iterate.c)
   
   > ```c
   > herr_t op_func (hid_t loc_id, const char *name, void *operator_data)
   > {
   >     herr_t          status;
   >     H5G_stat_t      statbuf;
   > 
   >     /*
   >      * Get type of the object and display its name and type.
   >      * The name of the object is passed to this function by
   >      * the Library.
   >      */
   >     status = H5Gget_objinfo (loc_id, name, 0, &statbuf);
   >     switch (statbuf.type) {
   >         case H5G_GROUP:
   >             printf ("  Group: %s\n", name);
   >             break;
   >         case H5G_DATASET:
   >             printf ("  Dataset: %s\n", name);
   >             break;
   >         case H5G_TYPE:
   >             printf ("  Datatype: %s\n", name);
   >             break;
   >         default:
   >             printf ( "  Unknown: %s\n", name);
   >     }
   > 
   >     return 0;
   > }
   > ```

8. Check if an attribute exists or not
   
   Use `H5Aexists` instead of `H5Lexists`.

9. H5::DataSet::extend will invalidate a data space
   
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

10. [Build both release and debug](https://forum.hdfgroup.org/t/build-both-release-and-debug/5094) & [HDF5 - Visual Studio - Build in Release works, Debug fails](https://forum.hdfgroup.org/t/hdf5-visual-studio-build-in-release-works-debug-fails/878)

11. [Iterative recording of real-time data over long time periods](https://forum.hdfgroup.org/t/iterative-recording-of-real-time-data-over-long-time-periods/6985)

12. [how to read hdf5 boolean enum created by h5py in C](https://stackoverflow.com/questions/11627376/how-to-read-hdf5-boolean-enum-created-by-h5py-in-c)

13. zlib linking issue when built as a static library
    
    - [Unresolved external symbol with zlib and libpng. Visual studio 2013](https://stackoverflow.com/questions/37762981/unresolved-external-symbol-with-zlib-and-libpng-visual-studio-2013)
      
      > For fixing the unresolved symbols problem, open zlib project  preferences,  then go to Configuration Properties -> C/C++ -> Preprocessor, and  in the Preprocessor Definitions line remove “ZLIB_WINAPI;” (don’t forget to remove the trailing semicolon).
    
    - [Unresolved externals despite linking in zlib.lib](https://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib)

14. https://github.com/hpc-io/h5bench

15. [How to flush a file?](https://github.com/BlueBrain/HighFive/blob/master/include/highfive/bits/H5File_misc.hpp)
    
    > ```c++
    > inline void File::flush() {
    > if (H5Fflush(_hid, H5F_SCOPE_GLOBAL) < 0) {
    >   HDF5ErrMapper::ToException<FileException>(
    >       std::string("Unable to flush file " + getName()));
    > }
    > }
    > ```
    
    [h5py flush not working](https://github.com/h5py/h5py/issues/1019)
    
    > https://github.com/h5py/h5py/blob/0981eee11b1a3a743a09adae852b062085b415b4/h5py/h5f.pyx#L129-L143

16. `H5Lexists` vs `H5Oexists_by_name`

17. How to copy/move all attributes from one dataset to another?
    
    - `H5Location::copyLink` vs `H5Location::moveLink`
    - `H5Lcopy` vs `H5Lmove`

18. How to open a file whose path is a `PCWSTR`?
    
    > ```
    > MyApp.exe!H5_get_utf16_str(const char * s)
    > MyApp.exe!Wopen_utf8(const char * path, int oflag, ...)
    > MyApp.exe!H5FD_sec2_open(const char * name, unsigned int flags, __int64 fapl_id, unsigned __int64 maxaddr)
    > MyApp.exe!H5FD_open(const char * name, unsigned int flags, __int64 fapl_id, unsigned __int64 maxaddr)
    > MyApp.exe!H5F__is_hdf5(const char * name, __int64 fapl_id)
    > MyApp.exe!H5VL__native_file_specific(void * obj, H5VL_file_specific_t specific_type, __int64 dxpl_id, void * * req, char * arguments)
    > MyApp.exe!H5VL__file_specific(void * obj, const H5VL_class_t * cls, H5VL_file_specific_t specific_type, __int64 dxpl_id, void * * req, char * arguments)
    > MyApp.exe!H5VL_file_specific(const H5VL_object_t * vol_obj, H5VL_file_specific_t specific_type, __int64 dxpl_id, void * * req, ...)
    > MyApp.exe!H5Fis_accessible(const char * filename, __int64 fapl_id)
    > MyApp.exe!H5::H5File::isHdf5(const char * name)
    > MyApp.exe!H5::H5File::isHdf5(const std::basic_string<char,std::char_traits<char>,std::allocator<char> > & name)
    > ```
    
    From the calling stack above, we can know that HDF5 assumes that the file path you passed to `H5File::isHdf5(const char * name)` is a UTF-8 string, not a ANSI one. So that is what we can do:
    
    > PCWSTR filePath = L"...";
    > 
    > const char *filePathU8 = WCharToUtf8(filePath);
    > 
    > assert(H5::H5File::isHdf5(filePathU8));

19. [Unifying Biological Image Formats with HDF5](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3016045/)

20. `selectHyperslab` C and C++ API
    
    C++:
    
    ```c++
    // `count` first, then `start`.
    void DataSpace::selectHyperslab(H5S_seloper_t op, const hsize_t *count, const hsize_t *start,
                               const hsize_t *stride, const hsize_t *block) const
    {
        // ...
    }
    ```
    
    C:
    
    ```c
    // `start` first, then `count`.
    herr_t H5Sselect_hyperslab(hid_t space_id, H5S_seloper_t op,
        const hsize_t start[], const hsize_t _stride[], const hsize_t count[],
        const hsize_t _block[]);
    ```

21. Object iteration
    
    - [Cookbook : Iteration](https://github.com/HDFGroup/HDF.PInvoke/wiki/Cookbook-:-Iteration)
    - https://github.com/HDFGroup/hdf5-examples/blob/master/1_6/C/H5G/h5ex_g_iterate.c
    - [How to Iterate over Group Members Using C](https://www.asc.ohio-state.edu/wilkins.5/computing/HDF/hdf5tutorial/iterate.html)
    - [HDF5 Cpp - retrieving the names of all groups in a file](https://stackoverflow.com/questions/23778630/hdf5-cpp-retrieving-the-names-of-all-groups-in-a-file)

22. [morphologica](https://github.com/ABRG-Models/morphologica)
    
    https://github.com/ABRG-Models/morphologica/blob/main/morph/HdfData.h

23. [MathNet.Numerics.Data.Matlab](https://github.com/mathnet/mathnet-numerics/tree/master/src/Data.Matlab)

24. Benchmark
   
   - [E3SM-IO](https://github.com/Parallel-NetCDF/E3SM-IO)

25. Softwares

   - [hdf5.viewer](https://github.com/HDF-NI/hdf5.viewer)
   - HDFView
   - ViTables

 26. https://github.com/neurodroid/stimfit/tree/master/src/libstfio/hdf5
 
