https://github.com/zeromq/czmq/issues/1972

Finally, I am able to build `czmq` (and almost all of its dependencies) successfully in `vcpkg`: https://github.com/microsoft/vcpkg/pull/4979
czmq depends on many 3rd party libraries (optional or required), and it is hard to handle all these dependencies correctly with `find_library`.

ZeroMQ, for example, can use `libsodium` optionally. And ZeroMQ's CMake module exports a target named `libzmq` (or `libzmq-static` with a static build). The exported CMake target file may looks like this (Windows, Debug mode):

```cmake
#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libzmq" for configuration "Debug"
set_property(TARGET libzmq APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libzmq PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/libzmq-mt-gd-4_3_2.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "${_IMPORT_PREFIX}/debug/lib/libsodium.lib;ws2_32;rpcrt4;iphlpapi"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/libzmq-mt-gd-4_3_2.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS libzmq )
list(APPEND _IMPORT_CHECK_FILES_FOR_libzmq "${_IMPORT_PREFIX}/debug/lib/libzmq-mt-gd-4_3_2.lib" "${_IMPORT_PREFIX}/debug/bin/libzmq-mt-gd-4_3_2.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
```

If the users use the exported CMake module in a CMake-based project like this:
```cmake
find_package(ZeroMQ CONFIG REQUIRED)
target_link_libraries(main PRIVATE libzmq)
```
then they don't worry about the `libsodium` dependency (It is already recorded in the `IMPORTED_LINK_INTERFACE_LIBRARIES_*` property of `libzmq` target).

If the users use `find_library` instead, they have to handle the `libsodium` dependency manually, and all the other platform specific libraries ZeroMQ may depends on. So, I replace `Findlibzmq.cmake` with this one in https://github.com/microsoft/vcpkg/pull/4979:
```cmake
find_package(ZeroMQ CONFIG REQUIRED)

set(LIBZMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})
set(LIBZMQ_LIBRARIES libzmq libzmq-static)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LIBZMQ
    REQUIRED_VARS LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS
)
```

and apply this patch to the cmake/Config.cmake.in:
```diff
diff --git a/builds/cmake/Config.cmake.in b/builds/cmake/Config.cmake.in
index 9c15f36a..e1475cd6 100644
--- a/builds/cmake/Config.cmake.in
+++ b/builds/cmake/Config.cmake.in
@@ -1,4 +1,14 @@
 @PACKAGE_INIT@

+include(CMakeFindDependencyMacro)
+
+find_dependency(ZeroMQ)
+
+if (@CZMQ_WITH_LIBCURL@ AND @LIBCURL_FOUND@)
+    find_dependency(OpenSSL)
+    find_dependency(ZLIB)
+endif ()
+
+
 include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake")
 check_required_components("@PROJECT_NAME@")
```

I noticed the existence of https://github.com/zeromq/czmq/pull/1939, and totally understand @bluca's concern. So a better solution should take both of the two cases into consideration:

```cmake
find_package(ZeroMQ CONFIG QUIET)
if (ZeroMQ_FOUND)
    set(ZMQ_CMAKE_MODULE_AVAILABLE 1)
else ()
    set(ZMQ_CMAKE_MODULE_AVAILABLE 0)
    # Fall back to find_library
    ......
endif ()
```

and in the `cmake/Config.cmake.in`:
```
if (@ZMQ_CMAKE_MODULE_AVAILABLE@)
    find_dependency(ZeroMQ)
endif ()
```

czmq's another optional dependency, libcurl, also faces this problem. libcurl itself may depends on OpenSSL, zlib, and others. So:
```cmake
find_library (
    LIBCURL_LIBRARIES
    NAMES curl
    HINTS ${PC_LIBCURL_LIBRARY_HINTS}
)
```
is not enough when libcurl is built as a static library. Besides, on Windows, the lib name of libcurl is not always libcurl.lib, so I have to take care of them this way:
```cmake
find_library(
    LIBCURL_LIBRARY_DEBUG
    NAMES libcurl-d_imp libcurl-d curl-d curl
)

find_library(
    LIBCURL_LIBRARY_RELEASE
    NAMES libcurl_imp libcurl curl
)
```

google-cloud-cpp handles libcurl dependency this way: https://github.com/googleapis/google-cloud-cpp/pull/2407/files

So you see, a generic Find*.cmake template sounds great, but it doesn't work all the time. If we can mantain those Find*.cmake standalone, then we may refine them freely. Otherwise, we have to use a bounch of `if else` in zproject_cmake.gsl to handle all the special cases when a generic solution is not enough (like what I did in https://github.com/zeromq/zproject/pull/1168).

If we do not want to go that far currently:
1. For *nix users, things seem not that bad. So, we do not have to change anything.
2. For Windows users with `vcpkg` (VS2015+ required), they may install czmq via:
   vcpkg install czmq:x86-windows
   or
   vcpkg install czmq[curl]:x86-windows
   to build czmq with libcurl.
3. For Windows users without `vcpkg` or with older versions of Visual Studio, they may use the deprecated Visual Studio solutions or CMake. And when they use CMake, they should handle czmq's indirect dependencies (libsodium, OpenSSL, zlib, etc.) themself or just forget about them if they don't need them.

OK. Before I close this issue, I want to do two more things:
1. Add `CZMQ_WITH_LIBCURL`, `CZMQ_WITH_LZ4`, `CZMQ_WITH_UUID` options to give the users more control over those optional 3rd dependencies so that I don't have to use a patch here: https://github.com/microsoft/vcpkg/pull/4979/files#diff-3aedb01dfe69985b0650dc857d7b6e1a
2. Update CZMQ's install instruction for Windows users.
