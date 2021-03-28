// clang-format off
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <H5Cpp.h>
// clang-format on

const char *DataSetName = "dataset";

H5std_string GetDateTime() {
  std::time_t now;
  std::time(&now);
  char buf[sizeof "2011-10-08T07:07:09Z"];
  std::strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
  return buf;
}

void WriteStringAttribute(H5::H5Object &obj, const char *attributeName,
                          const H5std_string &value) {
  if (!obj.attrExists(attributeName)) {
    H5::StrType strType(H5::PredType::C_S1, value.size());
    H5::DataSpace dataSpace(H5S_SCALAR);
    auto attribute = obj.createAttribute(attributeName, strType, dataSpace);
    attribute.write(strType, value);
  } else {
    auto attribute = obj.openAttribute(attributeName);
    attribute.write(attribute.getDataType(), value);
  }
}

H5std_string ReadStringAttribute(const H5::H5Object &obj,
                                 const char *attributeName) {
  if (!obj.attrExists(attributeName)) return "";

  H5std_string value;
  auto attribute = obj.openAttribute(attributeName);
  attribute.read(attribute.getDataType(), value);
  return value;
}

void WriteStringArrayAttribute(H5::H5Object &obj, const char *attributeName,
                               const std::vector<H5std_string> &value) {
  std::vector<const char *> cstrs(value.size());
  std::transform(value.cbegin(), value.cend(), cstrs.begin(),
                 [](const H5std_string &s) { return s.c_str(); });

  if (!obj.attrExists(attributeName)) {
    H5::StrType strType(H5::PredType::C_S1, H5T_VARIABLE);

    hsize_t dims[1]{static_cast<hsize_t>(value.size())};
    H5::DataSpace dataSpace(1, dims);

    auto attribute = obj.createAttribute(attributeName, strType, dataSpace);
    attribute.write(strType, cstrs.data());
  } else {
    auto attribute = obj.openAttribute(attributeName);
    attribute.write(attribute.getDataType(), cstrs.data());
  }
}

std::vector<H5std_string> ReadStringArrayAttribute(H5::H5Object &obj,
                                                   const char *attributeName) {
  std::vector<H5std_string> value;
  if (!obj.attrExists(attributeName)) return value;

  auto attribute = obj.openAttribute(attributeName);
  auto dataType = attribute.getDataType();
  if (dataType.getClass() != H5T_STRING) return value;

  auto dataSpace = attribute.getSpace();

  hsize_t dim;
  dataSpace.getSimpleExtentDims(&dim);

  std::vector<char *> cstrs(
      static_cast<std::vector<const char *>::size_type>(dim));
  H5::StrType strType(H5::PredType::C_S1, H5T_VARIABLE);
  attribute.read(strType, cstrs.data());

  value.resize(cstrs.size());
  std::transform(cstrs.cbegin(), cstrs.cend(), value.begin(),
                 [](const char *cstr) { return H5std_string(cstr); });

  // std::for_each(cstrs.begin(), cstrs.end(), [](char *p) { std::free(p); });
  H5Dvlen_reclaim(dataSpace.getId(), dataSpace.getId(), H5P_DEFAULT,
                  cstrs.data());

  return value;
}

void WriteFile(const H5std_string &filePath) {
  H5::H5File file(filePath, H5F_ACC_TRUNC);

  WriteStringAttribute(file, "created", GetDateTime());

  hsize_t dims[2]{3, 4};
  H5::DataSpace dataSpace(2, dims);
  H5::DSetCreatPropList propList;
  int fillValue = 42;
  propList.setFillValue(H5::PredType::NATIVE_INT, &fillValue);
  auto dataSet = file.createDataSet(DataSetName, H5::PredType::NATIVE_INT,
                                    dataSpace, propList);

  int array[4]{1, 2, 3, 4};
  hsize_t arrAttrDims[1]{4};
  H5::DataSpace arrAttrDataSpace(1, arrAttrDims);
  auto arrAttr = dataSet.createAttribute("array", H5::PredType::NATIVE_INT,
                                         arrAttrDataSpace);
  arrAttr.write(H5::PredType::NATIVE_INT, array);

  WriteStringAttribute(dataSet, "string", "Hello, world!");

  std::vector<H5std_string> columnNames;
  columnNames.push_back("Column 0");
  columnNames.push_back("Column 1");
  columnNames.push_back("Column 2");
  columnNames.push_back("Column 3");

  WriteStringArrayAttribute(dataSet, "names", columnNames);
}

void ReadFile(const H5std_string &filePath) {
  H5::H5File file(filePath, H5F_ACC_RDONLY);

  std::cout << ReadStringAttribute(file, "created") << std::endl;

  auto dataSet = file.openDataSet(DataSetName);

  if (dataSet.attrExists("array")) {
    auto arrAttr = dataSet.openAttribute("array");

    auto attrSpace = arrAttr.getSpace();
    hsize_t dims[1];
    attrSpace.getSimpleExtentDims(dims);

    std::vector<int> data(static_cast<std::vector<int>::size_type>(dims[0]));
    arrAttr.read(H5::PredType::NATIVE_INT, data.data());

    for (auto v : data) std::cout << v << ' ';
    std::cout << std::endl;
  }

  if (dataSet.attrExists("string")) {
    auto strAttr = dataSet.openAttribute("string");

    H5std_string string;

    H5::StrType strType(H5::PredType::C_S1, 5);
    strAttr.read(strType, string);
    std::cout << string << std::endl;

    H5::StrType strType2(H5::PredType::C_S1, 10);
    strAttr.read(strType2, string);
    std::cout << string << std::endl;

    // auto attrSpace = strAttr.getSpace();
    // hsize_t dims[64];
    // attrSpace.getSimpleExtentDims(dims);
    // std::cout << "String length: " << dims[0] << std::endl;

    std::cout << ReadStringAttribute(dataSet, "string") << std::endl;
  }

  auto names = ReadStringArrayAttribute(dataSet, "names");
  for (auto &name : names) std::cout << name << std::endl;
}

int main(int argc, char *argv[]) {
  try {
    H5::Exception::dontPrint();

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
// [How do I construct an ISO 8601 datetime in C++?](https://stackoverflow.com/questions/9527960/how-do-i-construct-an-iso-8601-datetime-in-c)
// [Store datetimes in HDF5 with H5Py](https://stackoverflow.com/questions/23570632/store-datetimes-in-hdf5-with-h5py)
// [HDF5: Do I need to to explicitly set the byte order?](https://stackoverflow.com/questions/48092082/hdf5-do-i-need-to-to-explicitly-set-the-byte-order)
// [Writing a comma separated string attribute to HDF5 dataset C++](https://stackoverflow.com/questions/23554387/writing-a-comma-separated-string-attribute-to-hdf5-dataset-c)
// https://support.hdfgroup.org/ftp/HDF5/examples/misc-examples/stratt.cpp
// https://github.com/HDFGroup/hdf5/blob/1.12/master/examples/h5_attribute.c
// [C/C++ HDF5 Read string attribute](https://stackoverflow.com/questions/31344648/c-c-hdf5-read-string-attribute)
// [How to read attributes in HDF5 file using C++ interface](https://stackoverflow.com/questions/43384261/how-to-read-attributes-in-hdf5-file-using-c-interface)
// https://support.hdfgroup.org/HDF5/doc1.6/UG/11_Datatypes.html
// [Reading a string array HDF5 Attribute in C++](https://stackoverflow.com/questions/43722194/reading-a-string-array-hdf5-attribute-in-c)
// https://support.hdfgroup.org/ftp/HDF5/examples/misc-examples/#attr
// https://support.hdfgroup.org/ftp/HDF5/examples/misc-examples/attrvstr.c
// https://portal.hdfgroup.org/display/HDF5/Examples+by+API
// https://forum.hdfgroup.org/t/error-reading-variable-length-utf8-string-using-h5lt-c-api/4392
// https://bitbucket.hdfgroup.org/projects/HDFFV/repos/hdf5-examples/browse/1_10/C/H5T/h5ex_t_vlstringatt.c
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_6/C/H5T/h5ex_t_vlstring.c
// clang-format on
