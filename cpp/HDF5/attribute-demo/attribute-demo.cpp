// clang-format off
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <H5Cpp.h>
// clang-format on

enum class Boolean : bool {
  False = 0,
  True = 1,
};

const char *DataSetName = "dataset";

H5std_string GetDateTime() {
  std::time_t now;
  std::time(&now);
  char buf[sizeof "2011-10-08T07:07:09Z"];
  std::strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
  return buf;
}

bool WriteStringAttribute(H5::H5Object &obj, const char *attributeName,
                          const H5std_string &value) {
  if (!obj.attrExists(attributeName)) {
    H5::StrType strType(H5::PredType::C_S1, value.size() + 1);
    // strType.setCset(H5T_CSET_UTF8);
    H5::DataSpace dataSpace(H5S_SCALAR);
    auto attribute = obj.createAttribute(attributeName, strType, dataSpace);
    attribute.write(strType, value);
  } else {
    auto attribute = obj.openAttribute(attributeName);

    auto dataSpace = attribute.getSpace();
    if (dataSpace.getSimpleExtentType() != H5S_SCALAR) return false;

    auto dataType = attribute.getDataType();
    if (dataType.getClass() != H5T_STRING) return false;

    attribute.write(dataType, value);
  }

  return true;
}

bool ReadStringAttribute(const H5::H5Object &obj, const char *attributeName,
                         H5std_string &value) {
  if (!obj.attrExists(attributeName)) return false;

  auto attribute = obj.openAttribute(attributeName);

  auto dataSpace = attribute.getSpace();
  if (dataSpace.getSimpleExtentType() != H5S_SCALAR) return false;

  auto dataType = attribute.getDataType();
  if (dataType.getClass() != H5T_STRING) return false;

  attribute.read(dataType, value);

  return true;
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
  // TODO: Can we use DataSet::vlenReclaim instead?
  H5Dvlen_reclaim(strType.getId(), dataSpace.getId(), H5P_DEFAULT,
                  cstrs.data());

  return value;
}

bool WriteIntAttribute(H5::H5Object &obj, const char *attributeName,
                       int value) {
  if (!obj.attrExists(attributeName)) {
    H5::DataSpace dataSpace(H5S_SCALAR);
    auto attribute =
        obj.createAttribute(attributeName, H5::PredType::NATIVE_INT, dataSpace);
    attribute.write(H5::PredType::NATIVE_INT, &value);
  } else {
    auto attribute = obj.openAttribute(attributeName);

    auto dataSpace = attribute.getSpace();
    if (dataSpace.getSimpleExtentType() != H5S_SCALAR) return false;

    auto dataType = attribute.getDataType();
    if (dataType.getClass() != H5T_INTEGER) return false;

    attribute.write(dataType, &value);
  }

  return true;
}

bool ReadIntAttribute(H5::H5Object &obj, const char *attributeName,
                      int &value) {
  if (!obj.attrExists(attributeName)) return false;

  auto attribute = obj.openAttribute(attributeName);
  if (attribute.getSpace().getSimpleExtentType() != H5S_SCALAR) return false;

  auto dataType = attribute.getDataType();
  if (dataType.getClass() != H5T_INTEGER) return false;

  attribute.read(dataType, &value);
  return true;
}

bool WriteDoubleAttribute(H5::H5Object &obj, const char *attributeName,
                          double value) {
  if (!obj.attrExists(attributeName)) {
    H5::DataSpace dataSpace(H5S_SCALAR);
    auto attribute = obj.createAttribute(
        attributeName, H5::PredType::NATIVE_DOUBLE, dataSpace);
    attribute.write(H5::PredType::NATIVE_DOUBLE, &value);
  } else {
    auto attribute = obj.openAttribute(attributeName);

    auto dataSpace = attribute.getSpace();
    if (dataSpace.getSimpleExtentType() != H5S_SCALAR) return false;

    auto dataType = attribute.getDataType();
    if (dataType.getClass() != H5T_FLOAT) return false;

    attribute.write(dataType, &value);
  }

  return true;
}

bool ReadDoubleAttribute(H5::H5Object &obj, const char *attributeName,
                         double &value) {
  if (!obj.attrExists(attributeName)) return false;

  auto attribute = obj.openAttribute(attributeName);
  if (attribute.getSpace().getSimpleExtentType() != H5S_SCALAR) return false;

  auto dataType = attribute.getDataType();
  if (dataType.getClass() != H5T_FLOAT) return false;

  attribute.read(dataType, &value);
  return true;
}

bool WriteDoubleArrayAttribute(H5::H5Object &obj, const char *attributeName,
                               const std::vector<double> &values) {
  if (!obj.attrExists(attributeName)) {
    hsize_t dims[1]{static_cast<hsize_t>(values.size())};
    H5::DataSpace dataSpace(1, dims);
    auto attribute = obj.createAttribute(
        attributeName, H5::PredType::NATIVE_DOUBLE, dataSpace);
    attribute.write(H5::PredType::NATIVE_DOUBLE, values.data());
  } else {
    auto attribute = obj.openAttribute(attributeName);

    auto dataSpace = attribute.getSpace();
    if (dataSpace.getSimpleExtentType() != H5S_SIMPLE) return false;

    auto dataType = attribute.getDataType();
    if (dataType.getClass() != H5T_FLOAT) return false;

    if (dataSpace.getSimpleExtentNdims() != 1) return false;

    hsize_t length;
    dataSpace.getSimpleExtentDims(&length);
    if (length > values.size()) return false;

    attribute.write(dataType, values.data());
  }

  return true;
}

bool ReadDoubleArrayAttribute(H5::H5Object &obj, const char *attributeName,
                              std::vector<double> &values) {
  values.clear();

  if (!obj.attrExists(attributeName)) return false;

  auto attribute = obj.openAttribute(attributeName);

  auto dataSpace = attribute.getSpace();
  if (dataSpace.getSimpleExtentNdims() != 1) return false;
  if (dataSpace.getSimpleExtentType() != H5S_SIMPLE) return false;

  hsize_t length;
  dataSpace.getSimpleExtentDims(&length);
  values.resize(static_cast<std::vector<double>::size_type>(length));

  auto dataType = attribute.getDataType();
  if (dataType.getClass() != H5T_FLOAT) return false;

  attribute.read(dataType, values.data());
  return true;
}

bool WriteBooleanAttribute(H5::H5Object &obj, const char *attributeName,
                           Boolean value) {
  if (!obj.attrExists(attributeName)) {
    H5::EnumType booleanType(H5::PredType::NATIVE_INT8);
    Boolean boolean = Boolean::False;
    booleanType.insert("FALSE", &boolean);
    boolean = Boolean::True;
    booleanType.insert("TRUE", &boolean);

    H5::DataSpace dataSpace(H5S_SCALAR);
    auto attribute =
        obj.createAttribute(attributeName, booleanType, dataSpace);
    attribute.write(booleanType, &value);
  } else {
    auto attribute = obj.openAttribute(attributeName);

    auto dataSpace = attribute.getSpace();
    if (dataSpace.getSimpleExtentType() != H5S_SCALAR) return false;

    auto dataType = attribute.getEnumType();

    attribute.write(dataType, &value);
  }

  return true;
}

bool ReadBooleanAttribute(H5::H5Object &obj, const char *attributeName,
                          Boolean &value) {
  if (!obj.attrExists(attributeName)) return false;

  auto attribute = obj.openAttribute(attributeName);
  if (attribute.getSpace().getSimpleExtentType() != H5S_SCALAR) return false;

  auto dataType = attribute.getEnumType();
  int members = dataType.getNmembers();
  for (int i = 0; i < members; ++i) {
    Boolean boolean;
    dataType.getMemberValue(i, &boolean);
    std::cout << dataType.nameOf(&boolean, 100) << " " << static_cast<bool>(boolean) << std::endl;
  }

  attribute.read(dataType, &value);
  return true;
}

bool IsDataSetExists(H5::H5Object &obj, const char *attributeName) {
  auto result = H5Lexists(obj.getId(), attributeName, H5P_DEFAULT);
  return result > 0;
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

  WriteIntAttribute(dataSet, "columns", 4);
  WriteDoubleAttribute(dataSet, "pi", 3.14159265358979);

  std::vector<double> factors{1.0, 2.0, 3.0, 4.0};
  WriteDoubleArrayAttribute(dataSet, "factors", factors);
  std::transform(factors.begin(), factors.end(), factors.begin(),
                 [](double x) { return x * x; });
  WriteDoubleArrayAttribute(dataSet, "factors", factors);

  WriteBooleanAttribute(dataSet, "boolean-8-bit-enum", Boolean::True);
}

void ReadFile(const H5std_string &filePath) {
  H5::H5File file(filePath, H5F_ACC_RDONLY);

  H5std_string created;
  if (ReadStringAttribute(file, "created", created))
    std::cout << created << std::endl;

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

    if (ReadStringAttribute(dataSet, "string", string))
      std::cout << string << std::endl;
  }

  std::cout << "Column names:\n";
  auto names = ReadStringArrayAttribute(dataSet, "names");
  for (auto &name : names) std::cout << name << std::endl;

  int columns;
  if (ReadIntAttribute(dataSet, "columns", columns))
    std::cout << "Total columns: " << columns << std::endl;

  double pi;
  if (ReadDoubleAttribute(dataSet, "pi", pi)) std::cout << pi << std::endl;

  std::vector<double> factors;
  if (ReadDoubleArrayAttribute(dataSet, "factors", factors)) {
    for (auto factor : factors) std::cout << factor << std::endl;
  }

  Boolean boolean;
  if (ReadBooleanAttribute(dataSet, "boolean-8-bit-enum", boolean))
    std::cout << static_cast<bool>(boolean) << std::endl;
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
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_14/C/H5T/h5ex_t_vlstringatt.c
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_6/C/H5T/h5ex_t_vlstring.c
// https://github.com/HDFGroup/hdf5/blob/develop/examples/h5_attribute.c
// [What datatype to use for UTF-8 text](https://forum.hdfgroup.org/t/what-datatype-to-use-for-utf-8-text/4829)
// [HDF5 Attribute unsigned long long value](https://stackoverflow.com/questions/27243947/hdf5-attribute-unsigned-long-long-value)
// https://github.com/HDFGroup/hdf5/issues/544
// https://github.com/HDFGroup/hdf5-examples/blob/master/1_14/C/H5T/h5ex_t_enum.c
// [HDF5 C++: How to get possible values of H5T_ENUM](https://stackoverflow.com/questions/58302430/hdf5-c-how-to-get-possible-values-of-h5t-enum)
// [How to create multi-value attribute in a HDF5 file using C++ API](https://stackoverflow.com/questions/35580279/how-to-create-multi-value-attribute-in-a-hdf5-file-using-c-api)
// clang-format on
