# Test 6a9b44345ca80c5422d91f72d4b5c56c31bec3d9

### On Win10:

```batch
cd /d E:\
git clone https://github.com/KjellKod/g3log
cd g3log
git checkout 6a9b44345ca80c5422d91f72d4b5c56c31bec3d9
mkdir build
cd build
```

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake ..
   cmake --build . --config Release --target install
   ```
   The installed files have this layout:
   ```
   E:/usr/local/lib/g3logger.lib
   E:/usr/local/bin/g3logger.dll
   E:/usr/local/include/g3log/active.hpp
   E:/usr/local/include/g3log/atomicbool.hpp
   E:/usr/local/include/g3log/crashhandler.hpp
   E:/usr/local/include/g3log/filesink.hpp
   E:/usr/local/include/g3log/future.hpp
   E:/usr/local/include/g3log/g3log.hpp
   E:/usr/local/include/g3log/logcapture.hpp
   E:/usr/local/include/g3log/loglevels.hpp
   E:/usr/local/include/g3log/logmessage.hpp
   E:/usr/local/include/g3log/logworker.hpp
   E:/usr/local/include/g3log/moveoncopy.hpp
   E:/usr/local/include/g3log/shared_queue.hpp
   E:/usr/local/include/g3log/sink.hpp
   E:/usr/local/include/g3log/sinkhandle.hpp
   E:/usr/local/include/g3log/sinkwrapper.hpp
   E:/usr/local/include/g3log/stacktrace_windows.hpp
   E:/usr/local/include/g3log/stlpatch_future.hpp
   E:/usr/local/include/g3log/time.hpp
   E:/usr/local/include/g3log/generated_definitions.hpp
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
   cmake .. -DCMAKE_INSTALL_PREFIX=./install
   cmake --build . --config Release --target install
   ```
   All files will be installed to `E:/g3log/build/install`.

   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using NSIS
   CPack: - Install project: g3log
   CPack: -   Install component: libraries
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/NSIS/g3log-1.3.2-win32/librariesE:/g3log/build/install
   CPack Error: Error when generating package: g3log
   ```
   Also note the temporary directory name in the error message.

3. Only specify `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_INSTALL_PREFIX=./win32-packaging
   cmake --build . --config Release --target install
   ```
   The installed files have this layout:
   ```
   C:/Program Files (x86)/./win32-packaging/lib/g3logger.lib
   C:/Program Files (x86)/./win32-packaging/bin/g3logger.dll
   C:/Program Files (x86)/./win32-packaging/include/g3log/active.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/atomicbool.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/crashhandler.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/filesink.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/future.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/g3log.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/logcapture.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/loglevels.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/logmessage.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/logworker.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/moveoncopy.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/shared_queue.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/sink.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/sinkhandle.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/sinkwrapper.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/stacktrace_windows.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/stlpatch_future.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/time.hpp
   C:/Program Files (x86)/./win32-packaging/include/g3log/generated_definitions.hpp
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets-debug.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   This time, I got a `g3log-1.3.2-win32.exe`. Install it:
   ```
   E:\g3log\build>tree /A /F "C:\Program Files (x86)\g3log 1.3.2"
   C:\PROGRAM FILES (X86)\G3LOG 1.3.2
   |   Uninstall.exe
   |
   \---win32-packaging
       \---win32-packaging
           +---bin
           |       g3logger.dll
           |
           \---include
               \---g3log
                       active.hpp
                       atomicbool.hpp
                       crashhandler.hpp
                       filesink.hpp
                       future.hpp
                       g3log.hpp
                       generated_definitions.hpp
                       logcapture.hpp
                       loglevels.hpp
                       logmessage.hpp
                       logworker.hpp
                       moveoncopy.hpp
                       shared_queue.hpp
                       sink.hpp
                       sinkhandle.hpp
                       sinkwrapper.hpp
                       stacktrace_windows.hpp
                       stlpatch_future.hpp
                       time.hpp
   ```

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=./install -DCPACK_PACKAGING_INSTALL_PREFIX=./win32-packaging
   cmake --build . --config Release --target install
   ```
   All files will be installed to `E:/g3log/build/install`.

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
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/NSIS/g3log-1.3.2-win32/librariesE:/g3log/build/install
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

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_INSTALL_PREFIX`:

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

3. Only specify `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_INSTALL_PREFIX=./linux-packaging
   make install
   ```
   The files will be installed to:
   ```
   /usr/local/./linux-packaging/lib/libg3logger.so.1.3.2-82
   /usr/local/./linux-packaging/lib/libg3logger.so
   /usr/local/./linux-packaging/include/g3log/active.hpp
   /usr/local/./linux-packaging/include/g3log/atomicbool.hpp
   /usr/local/./linux-packaging/include/g3log/crashhandler.hpp
   /usr/local/./linux-packaging/include/g3log/filesink.hpp
   /usr/local/./linux-packaging/include/g3log/future.hpp
   /usr/local/./linux-packaging/include/g3log/g3log.hpp
   /usr/local/./linux-packaging/include/g3log/logcapture.hpp
   /usr/local/./linux-packaging/include/g3log/loglevels.hpp
   /usr/local/./linux-packaging/include/g3log/logmessage.hpp
   /usr/local/./linux-packaging/include/g3log/logworker.hpp
   /usr/local/./linux-packaging/include/g3log/moveoncopy.hpp
   /usr/local/./linux-packaging/include/g3log/shared_queue.hpp
   /usr/local/./linux-packaging/include/g3log/sink.hpp
   /usr/local/./linux-packaging/include/g3log/sinkhandle.hpp
   /usr/local/./linux-packaging/include/g3log/sinkwrapper.hpp
   /usr/local/./linux-packaging/include/g3log/stacktrace_windows.hpp
   /usr/local/./linux-packaging/include/g3log/stlpatch_future.hpp
   /usr/local/./linux-packaging/include/g3log/time.hpp
   /usr/local/./linux-packaging/include/g3log/generated_definitions.hpp
   /usr/local/lib/cmake/g3logger/g3loggerTargets.cmake
   /usr/local/lib/cmake/g3logger/g3loggerTargets-release.cmake
   /usr/local/lib/cmake/g3logger/g3loggerConfig.cmake
   ```

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will be installed to:
   ```
   myd@ubuntu:~/g3log/build$ tree /linux-packaging/
   /linux-packaging/
   ├── lib
   │   └── cmake
   │       └── g3logger
   │           ├── g3loggerConfig.cmake
   │           ├── g3loggerTargets.cmake
   │           └── g3loggerTargets-release.cmake
   └── linux-packaging
       ├── include
       │   └── g3log
       │       ├── active.hpp
       │       ├── atomicbool.hpp
       │       ├── crashhandler.hpp
       │       ├── filesink.hpp
       │       ├── future.hpp
       │       ├── g3log.hpp
       │       ├── generated_definitions.hpp
       │       ├── logcapture.hpp
       │       ├── loglevels.hpp
       │       ├── logmessage.hpp
       │       ├── logworker.hpp
       │       ├── moveoncopy.hpp
       │       ├── shared_queue.hpp
       │       ├── sinkhandle.hpp
       │       ├── sink.hpp
       │       ├── sinkwrapper.hpp
       │       ├── stacktrace_windows.hpp
       │       ├── stlpatch_future.hpp
       │       └── time.hpp
       └── lib
           ├── libg3logger.so -> libg3logger.so.1.3.2-82
           └── libg3logger.so.1.3.2-82
   ```

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=./install -DCPACK_PACKAGING_INSTALL_PREFIX=./linux-packaging
   make install
   ```
   The files will be installed to `/home/myd/g3log/build/install`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/home/myd/g3log/build/install`.


# Test b30cd9360990fd439682e3543705aab7ea2d49fc

### On Win10:

```batch
cd /d E:\
git clone https://github.com/KjellKod/g3log
cd g3log
git checkout b30cd9360990fd439682e3543705aab7ea2d49fc
mkdir build
cd build
```

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake ..
   cmake --build . --config Release --target install
   ```
   The installed files have this layout:
   ```
   C:/Program Files (x86)/lib/g3logger.lib
   C:/Program Files (x86)/bin/g3logger.dll
   C:/Program Files (x86)/include/g3log/active.hpp
   C:/Program Files (x86)/include/g3log/atomicbool.hpp
   C:/Program Files (x86)/include/g3log/crashhandler.hpp
   C:/Program Files (x86)/include/g3log/filesink.hpp
   C:/Program Files (x86)/include/g3log/future.hpp
   C:/Program Files (x86)/include/g3log/g3log.hpp
   C:/Program Files (x86)/include/g3log/logcapture.hpp
   C:/Program Files (x86)/include/g3log/loglevels.hpp
   C:/Program Files (x86)/include/g3log/logmessage.hpp
   C:/Program Files (x86)/include/g3log/logworker.hpp
   C:/Program Files (x86)/include/g3log/moveoncopy.hpp
   C:/Program Files (x86)/include/g3log/shared_queue.hpp
   C:/Program Files (x86)/include/g3log/sink.hpp
   C:/Program Files (x86)/include/g3log/sinkhandle.hpp
   C:/Program Files (x86)/include/g3log/sinkwrapper.hpp
   C:/Program Files (x86)/include/g3log/stacktrace_windows.hpp
   C:/Program Files (x86)/include/g3log/stlpatch_future.hpp
   C:/Program Files (x86)/include/g3log/time.hpp
   C:/Program Files (x86)/include/g3log/generated_definitions.hpp
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets-release.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using ZIP
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: Create package
   CPack: - package: E:/g3log/build/g3log-1.3.2-win32.zip generated.
   ```

2. Only specify `CMAKE_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=C:/g3log
   cmake --build . --config Release --target install
   ```
   All files will be installed to `C:/g3log/`.

   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using ZIP
   CPack: Install projects
   CPack: - Install project: g3log
   CPack: Create package
   CPack: - package: E:/g3log/build/g3log-1.3.2-win32.zip generated.
   ```

3. Only specify `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_INSTALL_PREFIX=C:/g3log-package
   cmake --build . --config Release --target install
   ```
   The installed files have this layout:
   ```
   C:/Program Files (x86)/lib/g3logger.lib
   C:/Program Files (x86)/bin/g3logger.dll
   C:/Program Files (x86)/include/g3log/active.hpp
   C:/Program Files (x86)/include/g3log/atomicbool.hpp
   C:/Program Files (x86)/include/g3log/crashhandler.hpp
   C:/Program Files (x86)/include/g3log/filesink.hpp
   C:/Program Files (x86)/include/g3log/future.hpp
   C:/Program Files (x86)/include/g3log/g3log.hpp
   C:/Program Files (x86)/include/g3log/logcapture.hpp
   C:/Program Files (x86)/include/g3log/loglevels.hpp
   C:/Program Files (x86)/include/g3log/logmessage.hpp
   C:/Program Files (x86)/include/g3log/logworker.hpp
   C:/Program Files (x86)/include/g3log/moveoncopy.hpp
   C:/Program Files (x86)/include/g3log/shared_queue.hpp
   C:/Program Files (x86)/include/g3log/sink.hpp
   C:/Program Files (x86)/include/g3log/sinkhandle.hpp
   C:/Program Files (x86)/include/g3log/sinkwrapper.hpp
   C:/Program Files (x86)/include/g3log/stacktrace_windows.hpp
   C:/Program Files (x86)/include/g3log/stlpatch_future.hpp
   C:/Program Files (x86)/include/g3log/time.hpp
   C:/Program Files (x86)/include/g3log/generated_definitions.hpp
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerTargets-release.cmake
   C:/Program Files (x86)/lib/cmake/g3logger/g3loggerConfig.cmake
   ```
   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using ZIP
   CPack: Install projects
   CPack: - Install project: g3log
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/ZIP/g3log-1.3.2-win32C:/g3log-package
   CPack Error: Error when generating package: g3log
   ```

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=C:/g3log -DCPACK_PACKAGING_INSTALL_PREFIX=C:/g3log-package
   cmake --build . --config Release --target install
   ```
   All files will be installed to `C:/g3log/`.

   Create a package:
   ```
   cpack .
   ```
   Output:
   ```
   CPack: Create package using ZIP
   CPack: Install projects
   CPack: - Install project: g3log
   CPack Error: Problem creating temporary directory: E:/g3log/build/_CPack_Packages/win32/ZIP/g3log-1.3.2-win32C:/g3log-package
   CPack Error: Error when generating package: g3log
   ```

### On Ubuntu 17.10:

```batch
cd ~
git clone https://github.com/KjellKod/g3log
cd g3log
git checkout b30cd9360990fd439682e3543705aab7ea2d49fc
mkdir build
cd build
```

1. Do not specify `CMAKE_INSTALL_PREFIX` and `CPACK_PACKAGING_INSTALL_PREFIX`:

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
   cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/g3log
   make install
   ```
   The files will be installed to `/usr/local/g3log`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/usr/local/g3log`.

3. Only specify `CPACK_PACKAGING_INSTALL_PREFIX`:

   Build and install:
   ```cmake
   cmake .. -DCPACK_PACKAGING_INSTALL_PREFIX=/opt/g3log
   make install
   ```
   The files will be installed to `/usr/local`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will be installed to `/opt/g3log`.

4. Specify both of them:

   Build and install:
   ```cmake
   cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/g3log -DCPACK_PACKAGING_INSTALL_PREFIX=/opt/g3log
   make install
   ```
   The files will be installed to `/usr/local/g3log`.

   Create a package:
   ```
   make package
   ```
   Then install the `.deb` package, and all files will also be installed to `/opt/g3log`.


# References:
https://cmake.org/cmake/help/latest/variable/CPACK_PACKAGING_INSTALL_PREFIX.html

