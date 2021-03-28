// clang-format off
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <H5Cpp.h>

#include "endian_utils.h"
// clang-format on

const hsize_t kRank = 2;
const hsize_t kRows = 4;
const hsize_t kCols = 4;

const char *DataGroup = "/ByteOrderDemo";
const char *DataSetNative = "/ByteOrderDemo/DataSetNative";
const char *DataSetBE = "/ByteOrderDemo/DataSetBigEndian";
const char *DataSetLE = "/ByteOrderDemo/DataSetLittleEndian";

void WriteFile(const H5std_string &filePath) {
  // 1.
  H5::H5File file(filePath, H5F_ACC_TRUNC);

  // 2.
  auto group = file.createGroup(DataGroup);
  group.close();

  // Question: Can we reuse objects like fileSpace, dataType here?
  // 3.
  hsize_t dims[kRank]{kRows, kCols};
  hsize_t chunkDims[kRank]{1, kCols};
  H5::DataSpace fileSpace(kRank, dims);
  H5::DSetCreatPropList propList;
  propList.setChunk(kRank, chunkDims);
  propList.setDeflate(6);
  //
  auto dataSet = file.createDataSet(DataSetNative, H5::PredType::NATIVE_UINT32,
                                    fileSpace, propList);
  //
  H5::IntType dataType(H5::PredType::NATIVE_UINT32);
  dataType.setOrder(H5T_ORDER_BE);
  auto dataSetBE = file.createDataSet(DataSetBE, dataType, fileSpace, propList);
  //
  dataType.setOrder(H5T_ORDER_LE);
  auto dataSetLE = file.createDataSet(DataSetLE, dataType, fileSpace, propList);

  // 4.
  std::uint32_t data[kRows][kCols] = {
      {1, 2, 3, 4},
      {0x11, 0x22, 0x33, 0x44},
      {0x11FF, 0x22EE, 0x33DD, 0x44CC},
      {0xFFFFEEEE, 0xFFFFDDDD, 0xFFFFCCCC, 0xFFFFBBBB}};
  //
  dataSet.write(data, H5::PredType::NATIVE_UINT32);
  dataSetBE.write(data, H5::PredType::NATIVE_UINT32);
  dataSetLE.write(data, H5::PredType::NATIVE_UINT32);
}

void PrintData(const std::uint32_t (&data)[kRows][kCols]) {
  std::cout << std::hex;
  for (hsize_t i = 0; i < kRows; ++i) {
    for (hsize_t j = 0; j < kCols; ++j) std::cout << data[i][j] << ' ';
    std::cout << std::endl;
  }
}

void ReadFile(const H5std_string &filePath) {
  H5::H5File file(filePath, H5F_ACC_RDONLY);

  std::uint32_t data[kRows][kCols];

  auto dataSet = file.openDataSet(DataSetNative);
  dataSet.read(data, H5::PredType::NATIVE_UINT32);
  PrintData(data);

  std::memset(data, 0, sizeof(data));
  dataSet = file.openDataSet(DataSetBE);
  dataSet.read(data, H5::PredType::NATIVE_UINT32);
  PrintData(data);

  std::memset(data, 0, sizeof(data));
  dataSet = file.openDataSet(DataSetLE);
  dataSet.read(data, H5::PredType::NATIVE_UINT32);
  PrintData(data);
}

int main(int argc, char *argv[]) {
  try {
    H5::Exception::dontPrint();

    std::cout << "Host endianness: " << GetEndianName(GetHostEndian())
              << std::endl;

    H5std_string filePath = "./a.h5";
    WriteFile(filePath);
    ReadFile(filePath);
  } catch (H5::Exception error) {
    error.printErrorStack();
    return EXIT_FAILURE;
  }

  return 0;
}

// clang-format off
// References:
// [HDF5: Do I need to to explicitly set the byte order?](https://stackoverflow.com/questions/48092082/hdf5-do-i-need-to-to-explicitly-set-the-byte-order)
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/create.cpp
// https://github.com/HDFGroup/hdf5/blob/1.12/master/c%2B%2B/examples/h5group.cpp
// https://github.com/HDFGroup/hdf5/blob/develop/c%2B%2B/examples/h5tutr_subset.cpp
// https://forum.hdfgroup.org/t/getting-a-detailed-message-from-a-h5-exceptions/5976/6
// https://stackoverflow.com/questions/35522633/hdf5-consumes-all-resource-ids-for-dataspaces-and-exits-c-api
// https://support.hdfgroup.org/HDF5/doc1.6/UG/12_Dataspaces.html
// clang-format on
