Output(Win10 + VS2017):
```
-- CMAKE_LIBRARY_ARCHITECTURE:
-- CMAKE_PREFIX_PATH:
-- CMAKE_FRAMEWORK_PATH:
-- foo_LIBRARY: C:/Users/vcpkg/Ongoing-Study/cpp/CMake/find_libfoo_test/build/libfoo/lib/libfoo.lib
-- foo_LIBRARY:
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: C:/Users/vcpkg/Ongoing-Study/cpp/CMake/find_libfoo_test/build/libfoo/lib/libfoo.lib
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
```

Output(Win10 + MinGW-w64)
```
-- CMAKE_LIBRARY_ARCHITECTURE:
-- CMAKE_PREFIX_PATH:
-- CMAKE_FRAMEWORK_PATH:
-- foo_LIBRARY: C:/Users/vcpkg/Ongoing-Study/cpp/CMake/find_libfoo_test/build/libfoo/lib/liblibfoo.dll.a
-- foo_LIBRARY:
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: C:/Users/vcpkg/Ongoing-Study/cpp/CMake/find_libfoo_test/build/libfoo/lib/liblibfoo.dll.a
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
```

Output(Ubuntu):
```
-- CMAKE_LIBRARY_ARCHITECTURE: x86_64-linux-gnu
-- CMAKE_PREFIX_PATH: 
-- CMAKE_FRAMEWORK_PATH: 
-- foo_LIBRARY: /home/vcpkg/Desktop/find_libfoo_test/build/libfoo/lib/libfoo.so
-- foo_LIBRARY: 
-- foo_LIBRARY: /home/vcpkg/Desktop/find_libfoo_test/build/libfoo/lib/libfoo.so
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: foo_LIBRARY-NOTFOUND
-- foo_LIBRARY: /home/vcpkg/Desktop/find_libfoo_test/build/libfoo/lib/libfoo.so
```
