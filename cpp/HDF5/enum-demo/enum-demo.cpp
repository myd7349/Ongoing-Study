#include <iostream>

#include <H5Cpp.h>

enum class Boolean : unsigned char {
  False = 0,
  True = 1,
};

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

void Test(const H5std_string &filePath) {
  H5::H5File file(filePath, H5F_ACC_RDONLY);
  Boolean value;
  ReadBooleanAttribute(file, "boolean", value);
  std::cout << static_cast<bool>(value) << std::endl;
  file.close();
}

int main(int argc, char *argv[]) {
  try {
    H5::Exception::dontPrint();
    Test(argc >= 2 ? argv[1] : "a.h5");
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
