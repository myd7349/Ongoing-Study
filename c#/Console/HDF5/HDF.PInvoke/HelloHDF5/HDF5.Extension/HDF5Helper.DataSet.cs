namespace HDF5.Extension
{
    using System;
    using System.Linq;

    using HDF.PInvoke;

    using hid_t = System.Int64;

    public static partial class HDF5Helper
    {
        public static bool DataSetExists(hid_t hid, string dataSetName)
        {
            if (string.IsNullOrEmpty(dataSetName))
                throw new ArgumentException("dataSetName");

            var exists = H5L.exists(hid, dataSetName);
            if (exists < 0)
                throw new HDF5Exception("H5L.exists failed");

            if (exists == 0)
                return false;

            var objectId = H5O.open(hid, dataSetName);
            if (objectId < 0)
                throw new HDF5Exception("H5O.open failed");

            var result = DataSetExists(objectId);

            H5O.close(objectId);

            return result;
        }

        public static bool DataSetExists(hid_t dataSet)
        {
            return H5I.get_type(dataSet) == H5I.type_t.DATASET;
        }

        public static hid_t CreateDataSet(hid_t hid, string dataSetName, hid_t typeId, ulong[] dims, ulong[] maxDims = null, ulong[] chunk = null, object fillValue = null)
        {
            if (string.IsNullOrEmpty(dataSetName))
                throw new ArgumentException("dataSetName");

            if (dims == null)
                throw new ArgumentNullException("dims");

            if (maxDims != null && maxDims.Length != dims.Length)
                throw new ArgumentException("dims and maxDims should have the identical length.");

            var chunked = false;

            if (maxDims != null)
            {
                for (int i = 0; i < dims.Length; ++i)
                {
                    if (maxDims[i] != H5S.UNLIMITED && maxDims[i] < dims[i])
                        throw new ArgumentException("maxDims[i] < dims[i]");

                    if (!chunked)
                        chunked = maxDims[i] == H5S.UNLIMITED;
                }
            }

            if (chunked)
            {
                if (chunk == null)
                    throw new ArgumentNullException("chunk");

                if (chunk.Length != dims.Length)
                    throw new ArgumentException("chunk");

                if (chunk.Any(size => size <= 0))
                    throw new ArgumentException("All dimensions should have a positive length.");
            }

            if (DataSetExists(hid, dataSetName))
                throw new HDF5Exception("Data set \"{0}\" already exists.", dataSetName);

            var space = H5S.create_simple(dims.Length, dims, maxDims);
            if (space < 0)
                throw new HDF5Exception("H5S.create_simple failed.");

            if (!chunked)
            {
                var dataSet = H5D.create(hid, dataSetName, typeId, space);

                H5S.close(space);

                if (dataSet < 0)
                    throw new HDF5Exception("Failed to create data set \"{0}\".", dataSetName);

                return dataSet;
            }
            else
            {
                var createPropertyList = H5P.create(H5P.DATASET_CREATE);
                if (createPropertyList < 0)
                {
                    H5S.close(space);
                    throw new HDF5Exception("Failed to create property list for chunked data set \"{0}\".", dataSetName);
                }

                if (H5P.set_chunk(createPropertyList, chunk.Length, chunk) < 0)
                {
                    H5S.close(space);
                    throw new HDF5Exception("H5P.set_chunk failed.");
                }

                var dataSet = H5D.create(hid, dataSetName, typeId, space, H5P.DEFAULT, createPropertyList, H5P.DEFAULT);

                H5S.close(space);
                H5P.close(createPropertyList);

                if (dataSet < 0)
                    throw new HDF5Exception("Failed to create chunked data set \"{0}\".", dataSetName);

                return dataSet;
            }
        }

        public static void WriteDataSet(hid_t hid, string dataSetName, hid_t typeId)
        {
            if (string.IsNullOrEmpty(dataSetName))
                throw new ArgumentException("dataSetName");

            if (!DataSetExists(hid, "dataSetName"))
                throw new HDF5Exception("Data set \"{0}\" doesn't exist.", dataSetName);

            var dataSet = H5D.open(hid, dataSetName);
            if (dataSet < 0)
                throw new HDF5Exception("Failed to open data set \"{0}\".", dataSetName);

            try
            {
                WriteDataSet(dataSet, typeId);
            }
            finally
            {
                H5D.close(dataSet);
            }
        }

        public static void WriteDataSet(hid_t dataSet, hid_t typeId)
        {
        }

        public static void AppendDataSet(hid_t hid, string dataSetName, hid_t typeId, Array data)
        {
        }

        public static void AppendDataSet(hid_t dataSet, hid_t typeId, Array data)
        {
            if (data == null)
                throw new ArgumentNullException("data");

            var space = H5D.get_space(dataSet);
            if (space < 0)
                throw new HDF5Exception("Failed to get space of data set.");

            ulong[] dims = null;
            ulong[] maxDims = null;
            try
            {
                GetDataSpaceDimensions(space, ref dims, ref maxDims);
            }
            catch
            {
                H5S.close(space);
                throw;
            }

            var dataDims = Enumerable.Range(0, data.Rank)
                .Select(length => data.GetLength(length))
                //.Cast<ulong>()
                .ToArray();
            if (dataDims.Length > dims.Length)
            {
                H5S.close(space);
                throw new HDF5Exception("Data set rank: {0}, data rank: {1}.", dims.Length, dataDims.Length);
            }
        }

        public static int GetDataSetRank(hid_t dataSet)
        {
            var space = H5D.get_space(dataSet);
            if (space < 0)
                throw new HDF5Exception("Failed to get space of data set.");

            try
            {
                return GetDataSpaceRank(space);
            }
            finally
            {
                H5S.close(space);
            }
        }

        public static void GetDataSetDimensions(hid_t dataSet, ref ulong[] dims, ref ulong[] maxDims)
        {
            var space = H5D.get_space(dataSet);
            if (space < 0)
                throw new HDF5Exception("Failed to get space of data set.");

            try
            {
                GetDataSpaceDimensions(space, ref dims, ref maxDims);
            }
            finally
            {
                H5S.close(space);
            }
        }
    }
}
