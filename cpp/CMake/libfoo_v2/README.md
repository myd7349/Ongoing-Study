### On Win10:

```batch
cd /d E:\
git clone https://github.com/KjellKod/g3log
cd g3log
git checkout 6a9b44345ca80c5422d91f72d4b5c56c31bec3d9
mkdir build
cd build
```

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_PREFIX`:

   Build and install:
   ```cmake
   cmake ..
   cmake --build . --target install
   ```
   The installed files have this layout:
   ```
   C:/usr/local/lib/g3logger.lib
   C:/usr/local/bin/g3logger.dll
   C:/usr/local/include/g3log/active.hpp
   C:/usr/local/include/g3log/atomicbool.hpp
   C:/usr/local/include/g3log/crashhandler.hpp
   C:/usr/local/include/g3log/filesink.hpp
   C:/usr/local/include/g3log/future.hpp
   C:/usr/local/include/g3log/g3log.hpp
   C:/usr/local/include/g3log/logcapture.hpp
   C:/usr/local/include/g3log/loglevels.hpp
   C:/usr/local/include/g3log/logmessage.hpp
   C:/usr/local/include/g3log/logworker.hpp
   C:/usr/local/include/g3log/moveoncopy.hpp
   C:/usr/local/include/g3log/shared_queue.hpp
   C:/usr/local/include/g3log/sink.hpp
   C:/usr/local/include/g3log/sinkhandle.hpp
   C:/usr/local/include/g3log/sinkwrapper.hpp
   C:/usr/local/include/g3log/stacktrace_windows.hpp
   C:/usr/local/include/g3log/stlpatch_future.hpp
   C:/usr/local/include/g3log/time.hpp
   C:/usr/local/include/g3log/generated_definitions.hpp
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets-debug.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using NSIS
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: -   Install component: libraries
   CMake Error at E:/g3log/build/cmake_install.cmake:97 (message):
     ABSOLUTE path INSTALL DESTINATION forbidden (by caller):
     /usr/local/bin/g3logger.dll


   CPack Error: Error when generating package: g3log
   ```

2. Only specify `CMAKE_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=E:/g3log/build/install
   cmake --build . --target install
   ```
   The installed files have this layout:
   ```
   E:/g3log/build/install/lib/g3logger.lib
   E:/g3log/build/install/bin/g3logger.dll
   E:/g3log/build/install/include/g3log/active.hpp
   E:/g3log/build/install/include/g3log/atomicbool.hpp
   E:/g3log/build/install/include/g3log/crashhandler.hpp
   E:/g3log/build/install/include/g3log/filesink.hpp
   E:/g3log/build/install/include/g3log/future.hpp
   E:/g3log/build/install/include/g3log/g3log.hpp
   E:/g3log/build/install/include/g3log/logcapture.hpp
   E:/g3log/build/install/include/g3log/loglevels.hpp
   E:/g3log/build/install/include/g3log/logmessage.hpp
   E:/g3log/build/install/include/g3log/logworker.hpp
   E:/g3log/build/install/include/g3log/moveoncopy.hpp
   E:/g3log/build/install/include/g3log/shared_queue.hpp
   E:/g3log/build/install/include/g3log/sink.hpp
   E:/g3log/build/install/include/g3log/sinkhandle.hpp
   E:/g3log/build/install/include/g3log/sinkwrapper.hpp
   E:/g3log/build/install/include/g3log/stacktrace_windows.hpp
   E:/g3log/build/install/include/g3log/stlpatch_future.hpp
   E:/g3log/build/install/include/g3log/time.hpp
   E:/g3log/build/install/include/g3log/generated_definitions.hpp
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerTargets.cmake
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerTargets-debug.cmake
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using NSIS
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: -   Install component: libraries
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/NSIS/   g3log-1.3.2-win32/librariesE:/g3log/build/install
   CPack Error: Error when generating package: g3log
   ```

3. Only specify `CPACK_PACKAGING_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_PREFIX=E:/g3log/build/win32-packaging
   cmake --build . --target install
   ```
   The installed files have this layout:
   ```
   C:/usr/local/lib/g3logger.lib
   C:/usr/local/bin/g3logger.dll
   C:/usr/local/include/g3log/active.hpp
   C:/usr/local/include/g3log/atomicbool.hpp
   C:/usr/local/include/g3log/crashhandler.hpp
   C:/usr/local/include/g3log/filesink.hpp
   C:/usr/local/include/g3log/future.hpp
   C:/usr/local/include/g3log/g3log.hpp
   C:/usr/local/include/g3log/logcapture.hpp
   C:/usr/local/include/g3log/loglevels.hpp
   C:/usr/local/include/g3log/logmessage.hpp
   C:/usr/local/include/g3log/logworker.hpp
   C:/usr/local/include/g3log/moveoncopy.hpp
   C:/usr/local/include/g3log/shared_queue.hpp
   C:/usr/local/include/g3log/sink.hpp
   C:/usr/local/include/g3log/sinkhandle.hpp
   C:/usr/local/include/g3log/sinkwrapper.hpp
   C:/usr/local/include/g3log/stacktrace_windows.hpp
   C:/usr/local/include/g3log/stlpatch_future.hpp
   C:/usr/local/include/g3log/time.hpp
   C:/usr/local/include/g3log/generated_definitions.hpp
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets-debug.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using NSIS
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: -   Install component: libraries
   CMake Error at E:/g3log/build/cmake_install.cmake:97 (message):
     ABSOLUTE path INSTALL DESTINATION forbidden (by caller):
     /usr/local/bin/g3logger.dll


   CPack Error: Error when generating package: g3log
   ```

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=E:/g3log/build/install -DCPACK_PACKAGING_PREFIX=E:/g3log/build/win32-packaging
   cmake --build . --target install
   ```
   The installed files have this layout:
   ```
   E:/g3log/build/install/lib/g3logger.lib
   E:/g3log/build/install/bin/g3logger.dll
   E:/g3log/build/install/include/g3log/active.hpp
   E:/g3log/build/install/include/g3log/atomicbool.hpp
   E:/g3log/build/install/include/g3log/crashhandler.hpp
   E:/g3log/build/install/include/g3log/filesink.hpp
   E:/g3log/build/install/include/g3log/future.hpp
   E:/g3log/build/install/include/g3log/g3log.hpp
   E:/g3log/build/install/include/g3log/logcapture.hpp
   E:/g3log/build/install/include/g3log/loglevels.hpp
   E:/g3log/build/install/include/g3log/logmessage.hpp
   E:/g3log/build/install/include/g3log/logworker.hpp
   E:/g3log/build/install/include/g3log/moveoncopy.hpp
   E:/g3log/build/install/include/g3log/shared_queue.hpp
   E:/g3log/build/install/include/g3log/sink.hpp
   E:/g3log/build/install/include/g3log/sinkhandle.hpp
   E:/g3log/build/install/include/g3log/sinkwrapper.hpp
   E:/g3log/build/install/include/g3log/stacktrace_windows.hpp
   E:/g3log/build/install/include/g3log/stlpatch_future.hpp
   E:/g3log/build/install/include/g3log/time.hpp
   E:/g3log/build/install/include/g3log/generated_definitions.hpp
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerTargets.cmake
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerTargets-debug.cmake
   E:/g3log/build/install/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using NSIS
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: -   Install component: libraries
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/NSIS/   g3log-1.3.2-win32/librariesE:/g3log/build/install
   CPack Error: Error when generating package: g3log
   ```

### On Ubuntu 17.10:

```batch
cd ~
git clone https://github.com/KjellKod/g3log
cd g3log
git checkout 6a9b44345ca80c5422d91f72d4b5c56c31bec3d9
mkdir build
cd build
```

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_PREFIX`:

   Build and install:
   ```cmake
   cmake ..
   make install
   ```
   The files will be installed to `/usr/local`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/usr/local`.

2. Only specify `CMAKE_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=./install
   make install
   ```
   The files will be installed to `/home/myd/g3log/build/install`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/home/myd/g3log/build/install`.

3. Only specify `CPACK_PACKAGING_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_PREFIX=./linux-packaging
   make install
   ```
   The files will be installed to `/usr/local`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/usr/local`.

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=./install -DCPACK_PACKAGING_PREFIX=./linux-packaging
   make install
   ```
   The files will be installed to `/home/myd/g3log/build/install`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/home/myd/g3log/build/install`.
