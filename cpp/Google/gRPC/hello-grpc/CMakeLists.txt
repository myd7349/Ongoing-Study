cmake_minimum_required(VERSION 3.8)

project(hello-grpc LANGUAGES C CXX)

find_package(gRPC CONFIG REQUIRED)

set(proto_files
    helloworld.proto
)

add_library(greeter_proto ${proto_files})
target_link_libraries(greeter_proto
    PUBLIC
        gRPC::grpc++
        gRPC::grpc++_reflection
)
target_include_directories(greeter_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(greeter_proto PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/wd4251>)

#get_target_property(grpc_cpp_plugin_executable gRPC::grpc_cpp_plugin LOCATION)
set(grpc_cpp_plugin_executable $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

protobuf_generate(
    TARGET greeter_proto
    LANGUAGE cpp
)
protobuf_generate(
    TARGET greeter_proto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_executable}"
)

add_executable(greeter_server greeter_server.cc)
target_link_libraries(greeter_server PRIVATE greeter_proto)

add_executable(greeter_client greeter_client.cc)
target_link_libraries(greeter_client PRIVATE greeter_proto)


# References:
# https://grpc.io/blog/cmake-improvements/
# https://github.com/faaxm/exmpl-cmake-grpc/blob/master/proto/CMakeLists.txt
# https://github.com/grpc/grpc/blob/v1.40.0/examples/cpp/cmake/common.cmake
# https://www.f-ax.de/dev/2020/11/08/grpc-plugin-cmake-support.html
# https://stackoverflow.com/questions/68592085/how-to-generate-c-files-for-grpc-from-proto-files-on-windows-cross-platform
# [How to disable specific warning inherited from parent in Visual Studio?](https://stackoverflow.com/questions/41205725/how-to-disable-specific-warning-inherited-from-parent-in-visual-studio)
# [Getting rid of dll-interface warnings when compiling on Windows](https://github.com/cginternals/glbinding/issues/141)
