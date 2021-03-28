// clang-format off
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

#include <CLI/CLI.hpp>

#include <H5Cpp.h>

#include "high_timer.hpp"
// clang-format on

const int kRank = 2;

struct Options {
  H5std_string filePath{"./a.h5"};
  H5std_string dataSet{"dataset"};
  std::pair<hsize_t, hsize_t> offset{0, 0};
  std::pair<hsize_t, hsize_t> count{H5S_UNLIMITED, H5S_UNLIMITED};
};

void ReadFile(const Options &options) {
  // 1. File
  H5::H5File file(options.filePath, H5F_ACC_RDONLY);

  // 2. DataSet
  H5::DataSet dataSet = file.openDataSet(options.dataSet);

  // 3.
  auto fileSpace = dataSet.getSpace();
  auto rank = fileSpace.getSimpleExtentNdims();
  std::vector<hsize_t> dims(static_cast<std::vector<hsize_t>::size_type>(rank));
  std::vector<hsize_t> maxDims(dims.size());
  rank = fileSpace.getSimpleExtentDims(dims.data(), maxDims.data());
  //
  std::cout << "Rank: " << rank << std::endl;
  std::cout << "Dims: ";
  std::copy(dims.cbegin(), dims.cend(),
            std::ostream_iterator<hsize_t>(std::cout, " "));
  std::cout << std::endl;
  std::cout << "Max Dims: ";
  std::copy(maxDims.cbegin(), maxDims.cend(),
            std::ostream_iterator<hsize_t>(std::cout, " "));
  std::cout << std::endl;
  //
  std::vector<hsize_t> chunkDims(rank);
  auto propList = dataSet.getCreatePlist();
  auto chunked = propList.getLayout() == H5D_CHUNKED;
  std::cout << "Chunked: " << chunked << std::endl;
  if (chunked) {
    auto chunkSize = propList.getChunk(rank, chunkDims.data());
    std::cout << "Chunk size: " << chunkSize << std::endl;
    chunkDims.resize(chunkSize);
    std::cout << "Chunk Dims: ";
    std::copy(chunkDims.cbegin(), chunkDims.cend(),
              std::ostream_iterator<hsize_t>(std::cout, " "));
    std::cout << std::endl;
  }
  //
  propList.close();

  // 4. Read some data
  if (rank == 2) {
    hsize_t offset[2]{options.offset.first, options.offset.second};
    hsize_t count[2]{options.count.first, options.count.second};
    if (count[0] == H5S_UNLIMITED) count[0] = dims[0];
    if (count[1] == H5S_UNLIMITED) count[1] = dims[1];
    fileSpace.selectHyperslab(H5S_SELECT_SET, count, offset);

    H5::DataSpace memSpace(rank, count);
    std::vector<int> data(
        static_cast<std::vector<int>::size_type>(count[0] * count[1]));
    dataSet.read(data.data(), H5::PredType::NATIVE_INT32, memSpace, fileSpace);

    auto rows = static_cast<std::vector<int>::size_type>(count[0]);
    auto cols = static_cast<std::vector<int>::size_type>(count[1]);
    for (std::vector<int>::size_type i = 0; i < rows; ++i) {
      for (std::vector<int>::size_type j = 0; j < cols; ++j)
        std::cout << data[i * cols + j] << ' ';
      std::cout << std::endl;
    }
  }

  // 5. Clean
  fileSpace.close();
  dataSet.close();
  file.close();
}

int main(int argc, char *argv[]) {
  CLI::App app{"HDF5 hyperslabs benchmark."};

  Options options;
  app.add_option("-f,--file", options.filePath, "Specify output file path",
                 true);
  app.add_option("-d,--dataset", options.dataSet, "Specify dataset name", true);
  app.add_option("--offset", options.offset, "Specify offset", true);
  app.add_option("--count", options.count, "Specify count", true);

  CLI11_PARSE(app, argc, argv);

  try {
    H5::Exception::dontPrint();

    high_timer timer;

    ReadFile(options);

    std::cout << "Elapsed: " << timer.get_elapsed_ms() << "ms\n";
  } catch (H5::FileIException error) {
    error.printErrorStack();
    return EXIT_FAILURE;
  } catch (H5::DataSetIException error) {
    error.printErrorStack();
    return EXIT_FAILURE;
  } catch (H5::DataSpaceIException error) {
    error.printErrorStack();
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Unknown exception.\n";
    return EXIT_FAILURE;
  }

  return 0;
}

// clang-format off
// References:
// [Writing & Appending arrays of float to the only dataset in hdf5 file in C++](https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c)
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/examples/chunks.cpp
// https://cliutils.github.io/CLI11/book/
// clang-format on
