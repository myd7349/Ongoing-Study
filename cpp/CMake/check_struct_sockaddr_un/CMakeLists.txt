cmake_minimum_required(VERSION 3.8)

project(check_struct_sockaddr_un C)

include(CheckIncludeFiles)
include(CheckStructHasMember)

if(WIN32)
    check_include_files("winsock2.h;afunix.h" ZMQ_HAVE_IPC)

    if(ZMQ_HAVE_IPC)
        check_struct_has_member("struct _SOCKADDR_UN" sun_family "winsock2.h;afunix.h" HAVE_SOCKADDR_UN_FAMILY LANGUAGE C)
        check_struct_has_member("struct sockaddr_un" sun_family "winsock2.h;afunix.h" HAVE_sockaddr_un_FAMILY LANGUAGE C)
        check_struct_has_member("struct sockaddr_un" sun_path "winsock2.h;afunix.h" HAVE_sockaddr_un_PATH)
    endif()
endif()

add_executable(check_struct_sockaddr_un check_struct_sockaddr_un.c)


# References:
# [ZeroMQ BUILD_FAILED](https://github.com/microsoft/vcpkg/issues/21623)
# On danieljbarber's PC:
# typedef struct _SOCKADDR_UN
# {
#     ADDRESS_FAMILY Family;
#     wchar_t Path[63];
# } SOCKADDR_UN, *PSOCKADDR_UN;
# and on my PC:
# #define UNIX_PATH_MAX 108
# typedef struct sockaddr_un
# {
#     ADDRESS_FAMILY sun_family;
#     char sun_path[UNIX_PATH_MAX];
# } SOCKADDR_UN, *PSOCKADDR_UN;
# [Build fails with Visual C++ 2017 due to undefined sockaddr_un](https://github.com/zeromq/libzmq/issues/3949)
# [How to check whether a type exists (regardless of its size) with CMake?](https://stackoverflow.com/questions/50156364/how-to-check-whether-a-type-exists-regardless-of-its-size-with-cmake)
# https://devblogs.microsoft.com/commandline/af_unix-comes-to-windows/
# [AF_UNIX abstract on Windows do not work](https://github.com/microsoft/WSL/issues/4240)
# [AF_UNIX in windows](https://stackoverflow.com/questions/3872558/af-unix-in-windows)
# [AF_UNIX equivalent for Windows](https://stackoverflow.com/questions/9029174/af-unix-equivalent-for-windows)
# [Enable Unix-domain sockets support on Windows](https://git.furworks.de/opensourcemirror/postgresql/commit/8f3ec75de4060d86176ad4ac998eeb87a39748c2)
