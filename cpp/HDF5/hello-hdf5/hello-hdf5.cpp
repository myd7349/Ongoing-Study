// clang-format off
#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <H5Cpp.h>
// clang-format on

namespace fs = std::filesystem;

void write_hdf5_file(const H5std_string &path) {
  // clang-format off
  // H5F_ACC_CREAT will not work.
  // According to:
  // [HDF5 1.8.9:H5F_ACC_CREAT](https://forum.hdfgroup.org/t/hdf5-1-8-9-h5f-acc-creat/3317)
  // The flag H5F_ACC_CREAT is not supported in the main library and is removed
  // from the C++ API in this coming release. The documentation will show the
  // correct flags also, which are H5F_ACC_EXCL|H5F_ACC_TRUNC for creating new
  // files and H5F_ACC_RDONLY|H5F_ACC_RDWR for opening existing files.
  // H5::H5File file(path, H5F_ACC_CREAT); // <-- Doesn't work.
  // clang-format on
  H5::H5File file(path, H5F_ACC_TRUNC);

  H5::Group group(file.createGroup("group"));

  const int DIM0 = 3;
  const int DIM1 = 4;
  double data[DIM0][DIM1];

  for (std::size_t i = 0; i < DIM0; ++i) {
    for (std::size_t j = 0; j < DIM1; ++j) data[i][j] = (i + 1) * 10 + (j + 1);
  }

  const std::size_t RANK = 2;
  hsize_t shape[RANK] = {DIM0, DIM1};

  H5::DataSpace dataSpace(RANK, shape);

  H5::DataSet dataSet =
      group.createDataSet("dataset", H5::PredType::NATIVE_DOUBLE, dataSpace);

  dataSpace.close();

  dataSet.write(data, H5::PredType::NATIVE_DOUBLE);

  group.close();

  file.close();
}

int main(int argc, char *argv[]) {
  // H5::Exception::dontPrint();

  H5std_string file;
  if (argc >= 2)
    file = argv[1];
  else
    file = "./a.h5";

  if (fs::exists(file)) {
    std::cerr << "File \'" << file << "\' already exists.\n";
    return EXIT_FAILURE;
  }

  write_hdf5_file(file);

  return 0;
}

// clang-format off
// References:
// [HDF5 数据文件简介](https://zhuanlan.zhihu.com/p/104145585) - [blog](https://nono721.github.io/2020/02/15/hdf5.html)
// https://github.com/pachterlab/kallisto/issues/197
// > Can you try running this again but with the environment variable HDF5_USE_FILE_LOCKING=FALSE?
// [Can we disable h5py file locking for python file-like object?](https://stackoverflow.com/questions/57310333/can-we-disable-h5py-file-locking-for-python-file-like-object)
// clang-format on
