// clang-format off
#include <cstdlib>
#include <iostream>
#include <vector>

#include <CLI/CLI.hpp>

#include <H5Cpp.h>

#include "high_timer.hpp"
// clang-format on

const int kRank = 2;

struct Options {
  H5std_string filePath{"./a.h5"};
  H5std_string dataSet{"dataset"};
  int maxRows{1000000};
  int chunkRows{100};
  int columns{4};
};

void WriteToFile(const Options &options) {
  // 1. File
  H5::H5File file(options.filePath, H5F_ACC_TRUNC);

  // 2. DataSet
  // 2.1
  hsize_t dims[2]{0, 0};
  hsize_t maxDims[2]{H5S_UNLIMITED, options.columns};
  H5::DataSpace fileSpace(kRank, dims, maxDims);
  // 2.2
  H5::DSetCreatPropList propList;
  hsize_t chunkDims[2]{options.chunkRows, options.columns};
  propList.setChunk(kRank, chunkDims);
  // 2.3
  H5::DataSet dataSet = file.createDataSet(
      options.dataSet, H5::PredType::NATIVE_DOUBLE, fileSpace, propList);
  // 2.4
  fileSpace.close();
  propList.close();

  // 3. Write data to DataSet
  hsize_t start = 0;
  std::vector<double> buffer;
  while (start < options.maxRows) {
    // 3.1
    hsize_t rows = options.chunkRows;
    if (start + rows > options.maxRows) rows = options.maxRows - start;

    // 3.2
    buffer.resize(
        static_cast<std::vector<double>::size_type>(rows * options.columns));
    for (std::vector<double>::size_type i = 0; i < rows; ++i) {
      for (std::vector<double>::size_type j = 0; j < options.columns; ++j)
        buffer[i * options.columns + j] = static_cast<double>(start + i);
    }

    // 3.3
    hsize_t newDims[2]{start + rows, options.columns};
    dataSet.extend(newDims);

    // 3.4
    hsize_t offset[2]{start, 0};
    hsize_t extendedDims[2]{rows, options.columns};
    fileSpace = dataSet.getSpace();
    fileSpace.selectHyperslab(H5S_SELECT_SET, extendedDims, offset);
    H5::DataSpace memSpace(kRank, extendedDims);
    dataSet.write(buffer.data(), H5::PredType::NATIVE_DOUBLE, memSpace,
                  fileSpace);

    // 3.5
    memSpace.close();
    fileSpace.close();

    start += rows;
  }

  // 4. Clean
  dataSet.close();
  file.close();
}

int main(int argc, char *argv[]) {
  CLI::App app{"HDF5 hyperslabs benchmark."};

  Options options;
  app.add_option("-f,--file", options.filePath, "Specify output file path",
                 true);
  app.add_option("-d,--dataset", options.dataSet, "Specify dataset name", true);
  app.add_option("-r,--rows", options.maxRows, "Specify maximum rows", true)
      ->check(CLI::NonNegativeNumber);
  app.add_option("-C,--chunk-rows", options.chunkRows, "Specify chunk rows",
                 true)
      ->check(CLI::NonNegativeNumber);
  app.add_option("-c,--columns", options.columns, "Specify columns", true)
      ->check(CLI::NonNegativeNumber);

  CLI11_PARSE(app, argc, argv);

  if (options.chunkRows > options.maxRows) options.chunkRows = options.maxRows;

  try {
    H5::Exception::dontPrint();

    high_timer timer;

    WriteToFile(options);

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
  }

  return 0;
}

// clang-format off
// References:
// [Writing & Appending arrays of float to the only dataset in hdf5 file in C++](https://stackoverflow.com/questions/15379399/writing-appending-arrays-of-float-to-the-only-dataset-in-hdf5-file-in-c)
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/src/C2Cppfunction_map.htm
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/h5tutr_extend.cpp
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/extend_ds.cpp
// https://github.com/HDFGroup/hdf5/blob/develop/examples/h5_extend.c
// https://github.com/HDFGroup/hdf5/blob/develop/examples/h5_extend_write.c
// https://cliutils.github.io/CLI11/book/
// clang-format on
