// clang-format off
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
//#include <highfive/H5Easy.hpp>
#include <highfive/H5File.hpp>

#ifdef WCONV_AVAILABLE
#include "wconv.h"
#endif

namespace h5 = HighFive;
// clang-format on

const std::size_t DIM0 = 3;
const std::size_t DIM1 = 4;

enum class BooleanType : bool {
  FALSE = 0,
  TRUE = 1,
};

h5::EnumType<BooleanType> CreateBooleanType() {
  return { { "FALSE", BooleanType::FALSE }, { "TRUE", BooleanType::TRUE } };
}

HIGHFIVE_REGISTER_TYPE(BooleanType, CreateBooleanType)

std::string GetDateTime() {
  std::time_t now;
  std::time(&now);
  char buf[sizeof "2011-10-08T07:07:09Z"];
  std::strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
  return buf;
}

template <typename S, typename... Args>
void println(const S &format, const Args&... args) {
  fmt::print(format, args...);
  std::putc('\n', stdout);
}

void WriteToFile(const char *filePath) {
  h5::File file(filePath, h5::File::Overwrite);

#if 0
  H5Easy::dumpAttribute can only be used when the object is a dataset.
  H5Easy::dumpAttribute(file, "/", "created", GetDateTime());
#else
  file.createAttribute<std::string>("created", GetDateTime());
#endif

  int data[DIM0][DIM1]
  {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12}
  };
  auto dataSet = file.createDataSet<int>("dataset", h5::DataSpace::From(data));
  dataSet.write(data);

  int array[DIM1] { 1, 2, 3, 4 };
  dataSet.createAttribute("array", array);

  std::vector<std::string> columns
  {
    "Column 1",
    "Column 2",
    "Column 3",
    "Column 4",
  };
  dataSet.createAttribute("columns", columns);

  // This will not create a string attribute.
  dataSet.createAttribute("bytes", "Hello, world!");

  dataSet.createAttribute<std::string>("string", "Hello, world!");

  std::string hello = "Hello, world!";
  dataSet.createAttribute("string-2", hello);

  dataSet.createAttribute("pi", 3.1415926);

  dataSet.createAttribute<std::string>("good-morning-vlen", "早上好！");
#ifdef WCONV_AVAILABLE
  dataSet.createAttribute<std::string>("good-morning-vlen-encoded", AnsiToUtf8("早上好！"));
#endif

  // 8-bit integer with value 1.
  dataSet.createAttribute("boolean", true);

  // In Python, with h5py,
  // dataset.attrs['boolean'] = True
  // will create a 8-bit enum type:
  // 8-bit enum (0=FALSE, 1=TRUE)
#if 0
  auto booleanTypeAttribute = dataSet.createAttribute("boolean-8-bit-enum", h5::DataSpace(h5::DataSpace::datascape_scalar), CreateBooleanType());
  booleanTypeAttribute.write(BooleanType::TRUE);
#else
  dataSet.createAttribute("boolean-8-bit-enum", BooleanType::TRUE);
#endif
}

void ReadFromFile(const char *filePath) {
  h5::File file(filePath, h5::File::ReadOnly);

  std::string created;
  auto createdAttribute = file.getAttribute("created");
  createdAttribute.read(created);
  println("created: {}", created);

  int data[DIM0][DIM1];
  auto dataSet = file.getDataSet("dataset");
  dataSet.read(data);
  for (std::size_t i = 0; i < DIM0; ++i) {
    for (std::size_t j = 0; j < DIM1; ++j)
      std::cout << data[i][j] << ' ';
    std::cout << std::endl;
  }

  int array[DIM1];
  auto arrayAttribute = dataSet.getAttribute("array");
  arrayAttribute.read(array);
  //fmt::print("array: {}", array);
  //fmt::print("array: {}", fmt::format("{}", array));
  std::cout << "array: ";
  for (auto i : array)
    std::cout << i << ' ';
  std::cout << std::endl;

  auto columnsAttribute = dataSet.getAttribute("columns");
  std::vector<std::string> columns;
  columnsAttribute.read(columns);
  println("{}", columns);

  std::string hello;

  auto stringAttribute = dataSet.getAttribute("bytes");
  // This won't work:
  //stringAttribute.read(hello);
  std::vector<char> bytes;
  stringAttribute.read(bytes);
  println("bytes: {}", bytes.data());

  char ch14[14]{};
  stringAttribute.read(ch14);
  println("ch14: {}", ch14);

  stringAttribute = dataSet.getAttribute("string");
  stringAttribute.read(hello);
  println("string: {}", hello);

  stringAttribute = dataSet.getAttribute("string-2");
  stringAttribute.read(hello);
  println("string-2: {}", hello);

  stringAttribute = dataSet.getAttribute("good-morning-vlen");
  stringAttribute.read(hello);
  println("good-morning-vlen: {}", hello);

#ifdef WCONV_AVAILABLE
  stringAttribute = dataSet.getAttribute("good-morning-vlen-encoded");
  stringAttribute.read(hello);
  println("good-morning-vlen-encoded: {}", hello);
  println("good-morning-vlen-encoded-decoded: {}", Utf8ToAnsi(hello));
#endif

  auto doubleAttribute = dataSet.getAttribute("pi");
  double pi;
  doubleAttribute.read(pi);
  println("pi: {}", pi);

  auto booleanAttribute = dataSet.getAttribute("boolean");
  bool toBeOrNotToBe;
  booleanAttribute.read(toBeOrNotToBe);
  println("To be or not to be: {}", toBeOrNotToBe);

  booleanAttribute = dataSet.getAttribute("boolean-8-bit-enum");
  BooleanType toBeOrNotToBe2;
  booleanAttribute.read(toBeOrNotToBe2);
  println("To be or not to be 2: {}", toBeOrNotToBe2);
}

int main(int argc, char *argv[]) {
  const char *filePath = "a.h5";
  try {
    WriteToFile(filePath);
    ReadFromFile(filePath);
  } catch (h5::Exception &error) {
    std::cerr << error.what() << std::endl;
  }

  return 0;
}

// clang-format off
// References:
// https://github.com/BlueBrain/HighFive/blob/master/src/examples/easy_attribute.cpp
// https://github.com/BlueBrain/HighFive/blob/master/src/examples/create_attribute_string_integer.cpp
// https://github.com/BlueBrain/HighFive/blob/master/src/examples/create_dataset_double.cpp
// https://github.com/BlueBrain/HighFive/blob/master/src/examples/read_write_dataset_string.cpp
// [Why is println missing?](https://github.com/fmtlib/fmt/issues/428)
// https://danielae.github.io/fmt-MeetingCPP/MeetingC++2018/pdf/socializing-with-fmt.pdf
// https://github.com/fmtlib/fmt/blob/master/test/ranges-test.cc
// clang-format on
