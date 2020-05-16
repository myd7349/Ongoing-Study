#include <iostream>
#include <string>

struct PackageSpec {
  PackageSpec() noexcept = default;

  std::string name;
};

struct Type {
  enum {
    UNKNOWN,
    PORT,
    ALIAS,
  } type;
};

struct BinaryParagraph {
  BinaryParagraph();

  PackageSpec spec;
  Type type;

  void Dump() {
    std::cout << type.type << std::endl;
  }
};

BinaryParagraph::BinaryParagraph() = default;

int main() {
  BinaryParagraph bp;
  bp.Dump();
  std::cout << noexcept(std::string()) << std::endl;
  return 0;
}

// References:
// [Program with “noexcept” constructor accepted by gcc, rejected by clang](https://stackoverflow.com/questions/29483120/program-with-noexcept-constructor-accepted-by-gcc-rejected-by-clang)
// [Error using defaulted copy constructor: “deleted function”](https://stackoverflow.com/questions/32938907/error-using-defaulted-copy-constructor-deleted-function)
// [Is a defaulted constructor/assignment noexcept/constexpr by default?](https://stackoverflow.com/questions/36161188/is-a-defaulted-constructor-assignment-noexcept-constexpr-by-default)
/*
[root@instance-hswzyf6j vcpkg]# ./bootstrap-vcpkg.sh
-- The CXX compiler identification is GNU 7.3.1
-- Check for working CXX compiler: /opt/rh/devtoolset-7/root/usr/bin/g++
-- Check for working CXX compiler: /opt/rh/devtoolset-7/root/usr/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Detecting the C++ standard library
-- Detecting the C++ standard library - libstdc++
-- Detecting how to use the C++ filesystem library
-- Detecting how to use the C++ filesystem library - <experimental/filesystem> with -l[std]c++fs
-- Looking for C++ include pthread.h
-- Looking for C++ include pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Check if compiler accepts -pthread
-- Check if compiler accepts -pthread - yes
-- Found Threads: TRUE
-- Configuring done
-- Generating done
-- Build files have been written to: /root/myd/vcpkg/toolsrc/build.rel
[0/2] Re-checking globbed directories...
[19/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o
FAILED: CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o
/opt/rh/devtoolset-7/root/usr/bin/g++  -DVCPKG_DISABLE_METRICS=0 -DVCPKG_USE_STD_FILESYSTEM=0 -I../include -O3 -DNDEBUG   -pthread -std=c++1z -MD -MT CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o -MF CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o.d -o CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o -c ../src/vcpkg/binaryparagraph.cpp
../src/vcpkg/binaryparagraph.cpp:31:5: note: ‘vcpkg::BinaryParagraph::BinaryParagraph()’ is implicitly deleted because the default definition would be ill-formed:
     BinaryParagraph::BinaryParagraph() = default;
     ^~~~~~~~~~~~~~~
../src/vcpkg/binaryparagraph.cpp:31:5: error: use of deleted function ‘vcpkg::PackageSpec::PackageSpec()’
In file included from ../include/vcpkg/binaryparagraph.h:3:0,
                 from ../src/vcpkg/binaryparagraph.cpp:7:
../include/vcpkg/packagespec.h:22:9: note: ‘vcpkg::PackageSpec::PackageSpec() noexcept’ is implicitly deleted because its exception-specification does not match the implicit exception-specification ‘’
         PackageSpec() noexcept = default;
         ^~~~~~~~~~~
../src/vcpkg/binaryparagraph.cpp: In constructor ‘vcpkg::BinaryParagraph::BinaryParagraph(vcpkg::Parse::Paragraph)’:
../src/vcpkg/binaryparagraph.cpp:33:61: error: use of deleted function ‘vcpkg::PackageSpec::PackageSpec()’
     BinaryParagraph::BinaryParagraph(Parse::Paragraph fields)
                                                             ^
[24/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/commands.autocomplete.cpp.o
ninja: build stopped: subcommand failed.





[root@instance-hswzyf6j vcpkg]# ./bootstrap-vcpkg.sh
-- The CXX compiler identification is GNU 7.3.1
-- Check for working CXX compiler: /opt/rh/devtoolset-7/root/usr/bin/g++
-- Check for working CXX compiler: /opt/rh/devtoolset-7/root/usr/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Detecting the C++ standard library
-- Detecting the C++ standard library - libstdc++
-- Detecting how to use the C++ filesystem library
-- Detecting how to use the C++ filesystem library - <experimental/filesystem> with -l[std]c++fs
-- Looking for C++ include pthread.h
-- Looking for C++ include pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Check if compiler accepts -pthread
-- Check if compiler accepts -pthread - yes
-- Found Threads: TRUE
-- Configuring done
-- Generating done
-- Build files have been written to: /root/myd/vcpkg/toolsrc/build.rel
[0/2] Re-checking globbed directories...
[19/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o
FAILED: CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o
/opt/rh/devtoolset-7/root/usr/bin/g++  -DVCPKG_DISABLE_METRICS=0 -DVCPKG_USE_STD_FILESYSTEM=0 -I../include -O3 -DNDEBUG   -pthread -std=c++1z -MD -MT CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o -MF CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o.d -o CMakeFiles/vcpkglib.dir/src/vcpkg/binaryparagraph.cpp.o -c ../src/vcpkg/binaryparagraph.cpp
../src/vcpkg/binaryparagraph.cpp:31:5: note: ‘vcpkg::BinaryParagraph::BinaryParagraph()’ is implicitly deleted because the default definition would be ill-formed:
     BinaryParagraph::BinaryParagraph() = default;
     ^~~~~~~~~~~~~~~
../src/vcpkg/binaryparagraph.cpp:31:5: error: use of deleted function ‘vcpkg::PackageSpec::PackageSpec()’
In file included from ../include/vcpkg/binaryparagraph.h:3:0,
                 from ../src/vcpkg/binaryparagraph.cpp:7:
../include/vcpkg/packagespec.h:22:9: note: ‘vcpkg::PackageSpec::PackageSpec() noexcept’ is implicitly deleted because its exception-specification does not match the implicit exception-specification ‘’
         PackageSpec() noexcept = default;
         ^~~~~~~~~~~
../src/vcpkg/binaryparagraph.cpp: In constructor ‘vcpkg::BinaryParagraph::BinaryParagraph(vcpkg::Parse::Paragraph)’:
../src/vcpkg/binaryparagraph.cpp:33:61: error: use of deleted function ‘vcpkg::PackageSpec::PackageSpec()’
     BinaryParagraph::BinaryParagraph(Parse::Paragraph fields)
                                                             ^
[24/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/commands.autocomplete.cpp.o
ninja: build stopped: subcommand failed.


[root@instance-hswzyf6j vcpkg]# g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/opt/rh/devtoolset-7/root/usr/libexec/gcc/x86_64-redhat-linux/7/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/opt/rh/devtoolset-7/root/usr --mandir=/opt/rh/devtoolset-7/root/usr/share/man --infodir=/opt/rh/devtoolset-7/root/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --enable-plugin --with-linker-hash-style=gnu --enable-initfini-array --with-default-libstdcxx-abi=gcc4-compatible --with-isl=/builddir/build/BUILD/gcc-7.3.1-20180303/obj-x86_64-redhat-linux/isl-install --enable-libmpx --enable-gnu-indirect-function --with-tune=generic --with-arch_32=i686 --build=x86_64-redhat-linux
Thread model: posix
gcc version 7.3.1 20180303 (Red Hat 7.3.1-5) (GCC)

[50/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
FAILED: CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
/opt/rh/devtoolset-7/root/usr/bin/g++  -DVCPKG_DISABLE_METRICS=0 -DVCPKG_USE_STD_FILESYSTEM=0 -I../include -O3 -DNDEBUG   -pthread -std=c++1z -MD -MT CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o -MF CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o.d -o CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o -c ../src/vcpkg/packagespec.cpp
In file included from ../include/vcpkg/packagespec.h:3:0,
                 from ../src/vcpkg/packagespec.cpp:6:
../include/vcpkg/base/expected.h: In instantiation of ‘vcpkg::ExpectedT<T, S>::ExpectedT(S&&, vcpkg::ExpectedRightTag) [with T = vcpkg::FullPackageSpec; S = std::basic_string<char>]’:
../src/vcpkg/packagespec.cpp:67:109:   required from here
../include/vcpkg/base/expected.h:111:67: error: use of deleted function ‘vcpkg::ExpectedHolder<T>::ExpectedHolder() [with T = vcpkg::FullPackageSpec]’
         ExpectedT(S&& s, ExpectedRightTag = {}) : m_s(std::move(s)) {}
                                                                   ^
../include/vcpkg/base/expected.h:81:9: note: ‘vcpkg::ExpectedHolder<T>::ExpectedHolder() [with T = vcpkg::FullPackageSpec]’ is implicitly deleted because the default definition would be ill-formed:
         ExpectedHolder() = default;
         ^~~~~~~~~~~~~~
../include/vcpkg/base/expected.h:81:9: error: use of deleted function ‘vcpkg::FullPackageSpec::FullPackageSpec()’
In file included from ../src/vcpkg/packagespec.cpp:6:0:
../include/vcpkg/packagespec.h:99:9: note: ‘vcpkg::FullPackageSpec::FullPackageSpec() noexcept’ is implicitly deleted because its exception-specification does not match the implicit exception-specification ‘’
         FullPackageSpec() noexcept = default;
         ^~~~~~~~~~~~~~~
In file included from ../include/vcpkg/packagespec.h:3:0,
                 from ../src/vcpkg/packagespec.cpp:6:
../include/vcpkg/base/expected.h: In instantiation of ‘vcpkg::ExpectedT<T, S>::ExpectedT(const S&, vcpkg::ExpectedRightTag) [with T = vcpkg::FullPackageSpec; S = std::basic_string<char>]’:
../include/vcpkg/base/expected.h:216:64:   required from ‘U vcpkg::ExpectedT<T, S>::then(F) && [with F = vcpkg::FullPackageSpec::from_string(const string&, vcpkg::Triplet)::<lambda(vcpkg::ParsedQualifiedSpecifier&&)>; U = vcpkg::ExpectedT<vcpkg::FullPackageSpec, std::basic_string<char> >; T = vcpkg::ParsedQualifiedSpecifier; S = std::basic_string<char>]’
../src/vcpkg/packagespec.cpp:70:14:   required from here
../include/vcpkg/base/expected.h:110:61: error: use of deleted function ‘vcpkg::ExpectedHolder<T>::ExpectedHolder() [with T = vcpkg::FullPackageSpec]’
         ExpectedT(const S& s, ExpectedRightTag = {}) : m_s(s) {}


[51/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
FAILED: CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
/opt/rh/devtoolset-7/root/usr/bin/g++  -DVCPKG_DISABLE_METRICS=0 -DVCPKG_USE_STD                                                                                                 _FILESYSTEM=0 -I../include -O3 -DNDEBUG   -pthread -std=c++1z -MD -MT CMakeFiles                                                                                                 /vcpkglib.dir/src/vcpkg/packagespec.cpp.o -MF CMakeFiles/vcpkglib.dir/src/vcpkg/                                                                                                 packagespec.cpp.o.d -o CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o -c ..                                                                                                 /src/vcpkg/packagespec.cpp
In file included from ../include/vcpkg/packagespec.h:3:0,
                 from ../src/vcpkg/packagespec.cpp:6:
../include/vcpkg/base/expected.h: In instantiation of ‘vcpkg::ExpectedHolder<T>:                                                                                                 :ExpectedHolder() [with T = vcpkg::FullPackageSpec]’:
../include/vcpkg/base/expected.h:111:67:   required from ‘vcpkg::ExpectedT<T, S>                                                                                                 ::ExpectedT(S&&, vcpkg::ExpectedRightTag) [with T = vcpkg::FullPackageSpec; S =                                                                                                  std::basic_string<char>]’
../src/vcpkg/packagespec.cpp:67:109:   required from here
../include/vcpkg/base/expected.h:81:26: error: use of deleted function ‘vcpkg::F                                                                                                 ullPackageSpec::FullPackageSpec()’
         ExpectedHolder() {}
                          ^
In file included from ../src/vcpkg/packagespec.cpp:6:0:
../include/vcpkg/packagespec.h:99:9: note: ‘vcpkg::FullPackageSpec::FullPackageS                                                                                                 pec() noexcept’ is implicitly deleted because its exception-specification does n                                                                                                 ot match the implicit exception-specification ‘’
         FullPackageSpec() noexcept = default;
         ^~~~~~~~~~~~~~~
[56/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/install.cpp.o
ninja: build stopped: subcommand failed.


[50/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
FAILED: CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o
/opt/rh/devtoolset-7/root/usr/bin/g++  -DVCPKG_DISABLE_METRICS=0 -DVCPKG_USE_STD_FILESYSTEM=0 -I../include -O3 -DNDEBUG   -pthread -std=c++1z -MD -MT CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o -MF CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o.d -o CMakeFiles/vcpkglib.dir/src/vcpkg/packagespec.cpp.o -c ../src/vcpkg/packagespec.cpp
In file included from ../include/vcpkg/packagespec.h:3:0,
                 from ../src/vcpkg/packagespec.cpp:6:
../include/vcpkg/base/expected.h: In instantiation of ‘vcpkg::ExpectedHolder<T>::ExpectedHolder() [with T = vcpkg::FullPackageSpec]’:
../include/vcpkg/base/expected.h:111:67:   required from ‘vcpkg::ExpectedT<T, S>::ExpectedT(S&&, vcpkg::ExpectedRightTag) [with T = vcpkg::FullPackageSpec; S = std::basic_string<char>]’
../src/vcpkg/packagespec.cpp:67:109:   required from here
../include/vcpkg/base/expected.h:81:26: error: use of deleted function ‘vcpkg::FullPackageSpec::FullPackageSpec()’
         ExpectedHolder() {}
                          ^
In file included from ../src/vcpkg/packagespec.cpp:6:0:
../include/vcpkg/packagespec.h:99:9: note: ‘vcpkg::FullPackageSpec::FullPackageSpec() noexcept’ is implicitly deleted because its exception-specification does not match the implicit exception-specification ‘’
         FullPackageSpec() noexcept = default;
         ^~~~~~~~~~~~~~~
[55/75] Building CXX object CMakeFiles/vcpkglib.dir/src/vcpkg/install.cpp.o
ninja: build stopped: subcommand failed.
*/

/*
gcc7_3_1_build_error.cpp:29:1: note: ‘BinaryParagraph::BinaryParagraph()’ is implicitly deleted because the default definition would be ill-formed:
 BinaryParagraph::BinaryParagraph() = default;
 ^~~~~~~~~~~~~~~
gcc7_3_1_build_error.cpp:29:1: error: use of deleted function ‘PackageSpec::PackageSpec()’
gcc7_3_1_build_error.cpp:5:3: note: ‘PackageSpec::PackageSpec() noexcept’ is implicitly deleted because its exception-specification does not match the implicit exception-specification ‘’
   PackageSpec() noexcept = default;
   ^~~~~~~~~~~


$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/opt/rh/devtoolset-7/root/usr/libexec/gcc/x86_64-redhat-linux/7/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/opt/rh/devtoolset-7/root/usr --mandir=/opt/rh/devtoolset-7/root/usr/share/man --infodir=/opt/rh/devtoolset-7/root/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --enable-plugin --with-linker-hash-style=gnu --enable-initfini-array --with-default-libstdcxx-abi=gcc4-compatible --with-isl=/builddir/build/BUILD/gcc-7.3.1-20180303/obj-x86_64-redhat-linux/isl-install --enable-libmpx --enable-gnu-indirect-function --with-tune=generic --with-arch_32=i686 --build=x86_64-redhat-linux
Thread model: posix
gcc version 7.3.1 20180303 (Red Hat 7.3.1-5) (GCC)

$ ldd --version
ldd (GNU libc) 2.17
Copyright (C) 2012 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/
