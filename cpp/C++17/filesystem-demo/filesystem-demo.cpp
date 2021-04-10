#include CXX_FILESYSTEM_HEADER
#include <iostream>

namespace fs = CXX_FILESYSTEM_NAMESPACE;

int main(int argc, char *argv[]) {
  const char *file = "a.out";
  if (fs::exists(file))
    std::cout << "File \'" << file << "\' already exists.\n";
  else
    std::cout << "File \'" << file << "\' doesn't exist.\n";

  if (fs::exists(argv[0]))
    std::cout << "File \'" << argv[0] << "\' already exists.\n";
  else
    std::cout << "File \'" << argv[0] << "\' doesn't exist.\n";

  return 0;
}


// clang-format off
// References:
// [Why does GCC not seem to have the filesystem standard library?](https://stackoverflow.com/questions/45867379/why-does-gcc-not-seem-to-have-the-filesystem-standard-library)
// clang-format on

/*
[tom@localhost build]# g++ --version
g++ (GCC) 7.3.1 20180303 (Red Hat 7.3.1-5)
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

[tom@localhost build]# cmake ..
-- The CXX compiler identification is GNU 7.3.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /opt/rh/devtoolset-7/root/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Looking for C++ include filesystem
-- Looking for C++ include filesystem - not found
-- Looking for C++ include experimental/filesystem
-- Looking for C++ include experimental/filesystem - found
-- Performing Test CXX_FILESYSTEM_NO_LINK_NEEDED
-- Performing Test CXX_FILESYSTEM_NO_LINK_NEEDED - Failed
-- Performing Test CXX_FILESYSTEM_STDCPPFS_NEEDED
-- Performing Test CXX_FILESYSTEM_STDCPPFS_NEEDED - Success
-- CXX_FILESYSTEM_IS_EXPERIMENTAL: TRUE
-- CXX_FILESYSTEM_HAVE_FS: TRUE
-- CXX_FILESYSTEM_HEADER: experimental/filesystem
-- CXX_FILESYSTEM_NAMESPACE: std::experimental::filesystem
-- Configuring done
-- Generating done
*/
